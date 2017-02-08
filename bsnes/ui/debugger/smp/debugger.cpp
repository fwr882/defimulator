SMPDebugger smpDebugger;

void SMPDebugger::create() {
  Window::create(0, 0, 256, 256, "SMP Debugger");
  application.addWindow(this, "Debugger.SMPDebugger", "192,192");

  unsigned x = 5, y = 5;
  output.create(*this, x, y, 400, 200); x += 400 + 5;
  output.setFont(application.monospaceFont);
  output.setEditable(false);

  stepInto.create(*this, x, y, 80, Style::ButtonHeight, "Step Into"); y += Style::ButtonHeight;
  stepOver.create(*this, x, y, 80, Style::ButtonHeight, "Step Over"); y += Style::ButtonHeight;
  proceed.create(*this, x, y, 80, Style::ButtonHeight, "Proceed"); y += Style::ButtonHeight;
  proceed.setEnabled(false);

  setGeometry(0, 0, 490, 205);

  onClose = []() {
    debugger.showSMPDebugger.setChecked(false);
    return true;
  };

  stepInto.onTick = []() {
    debugger.debugMode = Debugger::DebugMode::StepIntoSMP;
  };

  stepOver.onTick = { &SMPDebugger::eventStepOver, this };
}

void SMPDebugger::synchronize() {
  stepInto.setEnabled(SNES::cartridge.loaded() && debugger.enableDebugger.checked() && breakpointEditor.runToBreakpoint.checked() == false);
  stepOver.setEnabled(stepInto.enabled() && SNES::smp.opcode_edge);
}

void SMPDebugger::refreshDisassembly() {
  uint16_t addr = SNES::smp.regs.pc;
  uint8_t *usage = SNES::smp.usage;

  signed offset[15];
  foreach(n, offset) n = -1;

  offset[7] = addr;

  //reverse disassembly
  for(signed n = 6; n >= 0; n--) {
    signed base = offset[n + 1];
    if(base == -1) break;

    for(unsigned r = 1; r <= 3; r++) {
      if(usage[(base - r) & 0xffff] & 0x20) {
        offset[n] = base - r;
        break;
      }
    }
  }

  //forward disassembly
  for(signed n = 8; n <= 14; n++) {
    signed base = offset[n - 1];
    if(base == -1) break;

    for(unsigned r = 1; r <= 3; r++) {
      if(usage[(base + r) & 0xffff] & 0x20) {
        offset[n] = base + r;
        break;
      }
    }
  }

  string buffer;
  for(unsigned n = 0; n < 15; n++) {
    buffer.append(n == 7 ? "> " : "  ");
    if(offset[n] == -1) {
      buffer.append("...\n");
    } else {
      uint16_t addr = offset[n];
      buffer.append(hex<4>(addr));
      buffer.append(" ");
      string text = SNESSMP::disassemble(
        addr, read(addr + 0), read(addr + 1), read(addr + 2)
      );

      buffer.append(text);
      buffer.append("\n");
    }
  }
  buffer.rtrim<1>("\n");
  output.setText(buffer);
}

void SMPDebugger::eventStepInto() {
  refreshDisassembly();
}

void SMPDebugger::eventStepOver() {
  uint8_t opcode = read(SNES::smp.regs.pc);
  unsigned length = SNESSMP::getOpcodeLength(opcode);
  SNES::smp.regs.pc += length;
  refreshDisassembly();
  console.eventTraceSMP();
}

uint8_t SMPDebugger::read(uint16_t addr) {
  return SNES::debugger.read(SNES::Debugger::MemorySource::APUBus, addr);
}
