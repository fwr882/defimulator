#include <snes/snes.hpp>

#define NECDSP_CPP
namespace SNES {

#include "memory.cpp"
#include "disassembler.cpp"
#include "serialization.cpp"
NECDSP necdsp;

void NECDSP::Enter() { necdsp.enter(); }

void NECDSP::enter() {
  while(true) {
    if(scheduler.sync == Scheduler::SynchronizeMode::All) {
      scheduler.exit(Scheduler::ExitReason::SynchronizeEvent);
    }

    exec();
    step(1);
    synchronize_cpu();
  }
}

void NECDSP::exec() {
  uint24 opcode = programROM[regs.pc++];
  switch(opcode >> 22) {
    case 0: exec_op(opcode); break;
    case 1: exec_rt(opcode); break;
    case 2: exec_jp(opcode); break;
    case 3: exec_ld(opcode); break;
  }

  int32 result = (int32)regs.k * regs.l;  //sign + 30-bit result
  regs.m = result >> 15;  //store sign + top 15-bits
  regs.n = result <<  1;  //store low 15-bits + zero
}

void NECDSP::exec_op(uint24 opcode) {
  uint2 pselect = opcode >> 20;  //P select
  uint4 alu     = opcode >> 16;  //ALU operation mode
  uint1 asl     = opcode >> 15;  //accumulator select
  uint2 dpl     = opcode >> 13;  //DP low modify
  uint4 dphm    = opcode >>  9;  //DP high XOR modify
  uint1 rpdcr   = opcode >>  8;  //RP decrement
  uint4 src     = opcode >>  4;  //move source
  uint4 dst     = opcode >>  0;  //move destination

  switch(src) {
    case  0: regs.idb = regs.trb; break;
    case  1: regs.idb = regs.a; break;
    case  2: regs.idb = regs.b; break;
    case  3: regs.idb = regs.tr; break;
    case  4: regs.idb = regs.dp; break;
    case  5: regs.idb = regs.rp; break;
    case  6: regs.idb = dataROM[regs.rp]; break;
    case  7: regs.idb = 0x8000 - regs.flaga.s1; break;
    case  8: regs.idb = regs.dr; regs.sr.rqm = 1; break;
    case  9: regs.idb = regs.dr; break;
    case 10: regs.idb = regs.sr; break;
    case 11: regs.idb = regs.si; break;  //MSB
    case 12: regs.idb = regs.si; break;  //LSB
    case 13: regs.idb = regs.k; break;
    case 14: regs.idb = regs.l; break;
    case 15: regs.idb = dataRAM[regs.dp]; break;
  }

  if(alu) {
    uint16 p, q, r;
    Flag flag;
    bool c;

    switch(pselect) {
      case 0: p = dataRAM[regs.dp]; break;
      case 1: p = regs.idb; break;
      case 2: p = regs.m; break;
      case 3: p = regs.n; break;
    }

    switch(asl) {
      case 0: q = regs.a; flag = regs.flaga; c = regs.flagb.c; break;
      case 1: q = regs.b; flag = regs.flagb; c = regs.flaga.c; break;
    }

    switch(alu) {
      case  1: r = q | p; break;                    //OR
      case  2: r = q & p; break;                    //AND
      case  3: r = q ^ p; break;                    //XOR
      case  4: r = q - p; break;                    //SUB
      case  5: r = q + p; break;                    //ADD
      case  6: r = q - p - c; break;                //SBB
      case  7: r = q + p + c; break;                //ADC
      case  8: r = q - 1; p = 1; break;             //DEC
      case  9: r = q + 1; p = 1; break;             //INC
      case 10: r = ~q; break;                       //CMP
      case 11: r = (q >> 1) | (q & 0x8000); break;  //SHR1 (ASR)
      case 12: r = (q << 1) | c; break;             //SHL1 (ROL)
      case 13: r = (q << 2) |  3; break;            //SHL2
      case 14: r = (q << 4) | 15; break;            //SHL4
      case 15: r = (q << 8) | (q >> 8); break;      //XCHG
    }

    flag.s0 = (r & 0x8000);
    flag.z = (r == 0);

    switch(alu) {
      case  1: case  2: case  3: case 10: case 13: case 14: case 15: {
        flag.c = 0;
        flag.ov0 = 0;
        flag.ov1 = 0;
        break;
      }
      case  4: case  5: case  6: case  7: case  8: case  9: {
        if(alu & 1) {
          //addition
          flag.ov0 = (q ^ r) & ~(q ^ p) & 0x8000;
          flag.c = (r < q);
        } else {
          //subtraction
          flag.ov0 = (q ^ r) &  (q ^ p) & 0x8000;
          flag.c = (r > q);
        }
        if(flag.ov0) {
          flag.s1 = flag.ov1 ^ !(r & 0x8000);
          flag.ov1 = !flag.ov1;
        }
        break;
      }
      case 11: {
        flag.c = q & 1;
        flag.ov0 = 0;
        flag.ov1 = 0;
        break;
      }
      case 12: {
        flag.c = q >> 15;
        flag.ov0 = 0;
        flag.ov1 = 0;
        break;
      }
    }

    switch(asl) {
      case 0: regs.a = r; regs.flaga = flag; break;
      case 1: regs.b = r; regs.flagb = flag; break;
    }
  }

  exec_ld((regs.idb << 6) + dst);

  switch(dpl) {
    case 1: regs.dp = (regs.dp & 0xf0) + ((regs.dp + 1) & 0x0f); break;  //DPINC
    case 2: regs.dp = (regs.dp & 0xf0) + ((regs.dp - 1) & 0x0f); break;  //DPDEC
    case 3: regs.dp = (regs.dp & 0xf0); break;  //DPCLR
  }

  regs.dp ^= dphm << 4;

  if(rpdcr) regs.rp--;
}

void NECDSP::exec_rt(uint24 opcode) {
  exec_op(opcode);
  regs.pc = regs.stack[--regs.sp];
}

void NECDSP::exec_jp(uint24 opcode) {
  uint9 brch = opcode >> 13;  //branch
  uint11 na  = opcode >>  2;  //next address
  uint2 bank = opcode >>  0;  //bank address

  uint16 jps = (regs.pc & 0x2000) | (bank << 11) | (na << 0);
  uint16 jpl = (bank << 11) | (na << 0);

  switch(brch) {
    case 0x000: regs.pc = regs.so; return;  //JMPSO

    case 0x080: if(regs.flaga.c == 0) regs.pc = jps; return;  //JNCA
    case 0x082: if(regs.flaga.c == 1) regs.pc = jps; return;  //JCA
    case 0x084: if(regs.flagb.c == 0) regs.pc = jps; return;  //JNCB
    case 0x086: if(regs.flagb.c == 1) regs.pc = jps; return;  //JCB

    case 0x088: if(regs.flaga.z == 0) regs.pc = jps; return;  //JNZA
    case 0x08a: if(regs.flaga.z == 1) regs.pc = jps; return;  //JZA
    case 0x08c: if(regs.flagb.z == 0) regs.pc = jps; return;  //JNZB
    case 0x08e: if(regs.flagb.z == 1) regs.pc = jps; return;  //JZB

    case 0x090: if(regs.flaga.ov0 == 0) regs.pc = jps; return;  //JNOVA0
    case 0x092: if(regs.flaga.ov0 == 1) regs.pc = jps; return;  //JOVA0
    case 0x094: if(regs.flagb.ov0 == 0) regs.pc = jps; return;  //JNOVB0
    case 0x096: if(regs.flagb.ov0 == 1) regs.pc = jps; return;  //JOVB0

    case 0x098: if(regs.flaga.ov1 == 0) regs.pc = jps; return;  //JNOVA1
    case 0x09a: if(regs.flaga.ov1 == 1) regs.pc = jps; return;  //JOVA1
    case 0x09c: if(regs.flagb.ov1 == 0) regs.pc = jps; return;  //JNOVB1
    case 0x09e: if(regs.flagb.ov1 == 1) regs.pc = jps; return;  //JOVB1

    case 0x0a0: if(regs.flaga.s0 == 0) regs.pc = jps; return;  //JNSA0
    case 0x0a2: if(regs.flaga.s0 == 1) regs.pc = jps; return;  //JSA0
    case 0x0a4: if(regs.flagb.s0 == 0) regs.pc = jps; return;  //JNSB0
    case 0x0a6: if(regs.flagb.s0 == 1) regs.pc = jps; return;  //JSB0

    case 0x0a8: if(regs.flaga.s1 == 0) regs.pc = jps; return;  //JNSA1
    case 0x0aa: if(regs.flaga.s1 == 1) regs.pc = jps; return;  //JSA1
    case 0x0ac: if(regs.flagb.s1 == 0) regs.pc = jps; return;  //JNSB1
    case 0x0ae: if(regs.flagb.s1 == 1) regs.pc = jps; return;  //JSB1

    case 0x0b0: if((regs.dp & 0x0f) == 0x00) regs.pc = jps; return;  //JDPL0
    case 0x0b1: if((regs.dp & 0x0f) != 0x00) regs.pc = jps; return;  //JDPLN0
    case 0x0b2: if((regs.dp & 0x0f) == 0x0f) regs.pc = jps; return;  //JDPLF
    case 0x0b3: if((regs.dp & 0x0f) != 0x0f) regs.pc = jps; return;  //JDPLNF

    case 0x0bc: if(regs.sr.rqm == 0) regs.pc = jps; return;  //JNRQM
    case 0x0be: if(regs.sr.rqm == 1) regs.pc = jps; return;  //JRQM

    case 0x100: regs.pc = 0x0000 | jpl; return;  //LJMP
    case 0x101: regs.pc = 0x2000 | jpl; return;  //HJMP

    case 0x140: regs.stack[regs.sp++] = regs.pc; regs.pc = 0x0000 | jpl; return;  //LCALL
    case 0x141: regs.stack[regs.sp++] = regs.pc; regs.pc = 0x2000 | jpl; return;  //HCALL
  }
}

void NECDSP::exec_ld(uint24 opcode) {
  uint16 id = opcode >> 6;  //immediate data
  uint4 dst = opcode >> 0;  //destination

  regs.idb = id;

  switch(dst) {
    case  0: break;
    case  1: regs.a = id; break;
    case  2: regs.b = id; break;
    case  3: regs.tr = id; break;
    case  4: regs.dp = id; break;
    case  5: regs.rp = id; break;
    case  6: regs.dr = id; regs.sr.rqm = 1; break;
    case  7: regs.sr = (regs.sr & 0x907c) | (id & ~0x907c); break;
    case  8: regs.so = id; break;  //LSB
    case  9: regs.so = id; break;  //MSB
    case 10: regs.k = id; break;
    case 11: regs.k = id; regs.l = dataROM[regs.rp]; break;
    case 12: regs.l = id; regs.k = dataRAM[regs.dp | 0x40]; break;
    case 13: regs.l = id; break;
    case 14: regs.trb = id; break;
    case 15: dataRAM[regs.dp] = id; break;
  }
}

void NECDSP::init() {
}

void NECDSP::enable() {
}

void NECDSP::power() {
  if(revision == Revision::uPD7725) {
    regs.pc.bits(11);
    regs.rp.bits(10);
    regs.dp.bits( 8);
    dpmask = 0x000000, dptest = 0xffffff;  //uPD7725 not mapped to SNES bus
  }

  if(revision == Revision::uPD96050) {
    regs.pc.bits(14);
    regs.rp.bits(11);
    regs.dp.bits(11);
  }

  reset();
}

void NECDSP::reset() {
  create(NECDSP::Enter, frequency);

  for(unsigned n = 0; n < 16; n++) regs.stack[n] = 0x0000;
  regs.pc = 0x0000;
  regs.rp = 0x0000;
  regs.dp = 0x0000;
  regs.sp = 0x0;
  regs.k = 0x0000;
  regs.l = 0x0000;
  regs.m = 0x0000;
  regs.n = 0x0000;
  regs.a = 0x0000;
  regs.b = 0x0000;
  regs.flaga = 0x00;
  regs.flagb = 0x00;
  regs.tr = 0x0000;
  regs.trb = 0x0000;
  regs.sr = 0x0000;
  regs.dr = 0x0000;
  regs.si = 0x0000;
  regs.so = 0x0000;
  regs.idb = 0x0000;
}

NECDSP::NECDSP() {
}

NECDSP::~NECDSP() {
}

}
