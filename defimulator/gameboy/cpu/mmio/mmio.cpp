#ifdef CPU_CPP

void CPU::mmio_joyp_poll(void)
{
  unsigned button = 0, dpad = 0;

  button |= system.interface->input_poll((unsigned)Input::Start) << 3;
  button |= system.interface->input_poll((unsigned)Input::Select) << 2;
  button |= system.interface->input_poll((unsigned)Input::B) << 1;
  button |= system.interface->input_poll((unsigned)Input::A) << 0;

  dpad |= system.interface->input_poll((unsigned)Input::Down) << 3;
  dpad |= system.interface->input_poll((unsigned)Input::Up) << 2;
  dpad |= system.interface->input_poll((unsigned)Input::Left) << 1;
  dpad |= system.interface->input_poll((unsigned)Input::Right) << 0;

  status.joyp = 0x0f;
  if(status.p15 == 1 && status.p14 == 1) status.joyp -= status.mlt_req;
  if(status.p15 == 0) status.joyp &= button ^ 0x0f;
  if(status.p14 == 0) status.joyp &= dpad ^ 0x0f;
  if(status.joyp != 0x0f) interrupt_raise(Interrupt::Joypad);
}

uint8 CPU::mmio_read(uint16 addr)
{
  if(addr >= 0xc000 && addr <= 0xdfff) return wram[addr & 0x1fff];
  if(addr >= 0xe000 && addr <= 0xfdff) return wram[addr & 0x1fff];
  if(addr >= 0xff80 && addr <= 0xfffe) return hram[addr & 0x7f];

  if(addr == 0xff00) {  //JOYP
    return (status.p15 << 5)
         | (status.p14 << 4)
         | (status.joyp << 0);
  }

  if(addr == 0xff04) {  //DIV
    return status.div;
  }

  if(addr == 0xff05) {  //TIMA
    return status.tima;
  }

  if(addr == 0xff06) {  //TMA
    return status.tma;
  }

  if(addr == 0xff07) {  //TAC
    return (status.timer_enable << 2)
         | (status.timer_clock << 0);
  }

  if(addr == 0xff0f) {  //IF
    return (status.interrupt_request_joypad << 4)
         | (status.interrupt_request_serial << 3)
         | (status.interrupt_request_timer << 2)
         | (status.interrupt_request_stat << 1)
         | (status.interrupt_request_vblank << 0);
  }

  if(addr == 0xffff) {  //IE
    return (status.interrupt_enable_joypad << 4)
         | (status.interrupt_enable_serial << 3)
         | (status.interrupt_enable_timer << 2)
         | (status.interrupt_enable_stat << 1)
         | (status.interrupt_enable_vblank << 0);
  }

  return 0x00;
}

void CPU::mmio_write(uint16 addr, uint8 data)
{
    if (addr >= 0xc000 && addr <= 0xdfff) {
        wram[addr & 0x1fff] = data;
        return;
    }

    if (addr >= 0xe000 && addr <= 0xfdff) {
        wram[addr & 0x1fff] = data;
        return;
    }

    if (addr >= 0xff80 && addr <= 0xfffe) {
        hram[addr & 0x7f] = data;
        return;
    }

    /* JOYP */
    if (addr == 0xff00) {
        status.p15 = data & 0x20;
        status.p14 = data & 0x10;
        system.interface->joyp_write(status.p15, status.p14);
        mmio_joyp_poll();
        return;
    }

    /* SB */
    if (addr == 0xff01) {
        return;
    }
 
    /* SC */
    if (addr == 0xff02) {
        return;
    }

    /* DIV */
    if (addr == 0xff04) {
        status.div = 0;
        return;
    }

    /* TIMA */
    if (addr == 0xff05) {
        status.tima = data;
        return;
    }

    /* TMA */
    if (addr == 0xff06) {
        status.tma = data;
        return;
    }

    /* TAC */
    if (addr == 0xff07) {
        status.timer_enable = data & 0x04;
        status.timer_clock = data & 0x03;
        return;
    }

    /* IF */
    if (addr == 0xff0f) {
        status.interrupt_request_joypad = data & 0x10;
        status.interrupt_request_serial = data & 0x08;
        status.interrupt_request_timer = data & 0x04;
        status.interrupt_request_stat = data & 0x02;
        status.interrupt_request_vblank = data & 0x01;
        return;
    }

    /* IE */
    if (addr == 0xffff) {
        status.interrupt_enable_joypad = data & 0x10;
        status.interrupt_enable_serial = data & 0x08;
        status.interrupt_enable_timer = data & 0x04;
        status.interrupt_enable_stat = data & 0x02;
        status.interrupt_enable_vblank = data & 0x01;
        return;
    }
}

#endif
