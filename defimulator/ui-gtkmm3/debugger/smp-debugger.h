#ifndef DEFIMULATOR_UI_DEBUGGER_SMPDEBUGGER_H
#define DEFIMULATOR_UI_DEBUGGER_SMPDEBUGGER_H

#include <ui/base.hpp>

struct SMPDebugger : TopLevelWindow {
    EditBox output;
    Button stepInto;
    Button stepOver;
    Button proceed;

    void create(void);
    void synchronize(void);
    void refreshDisassembly(void);
    void eventStepInto(void);
    void eventStepOver(void);

    uint8_t read(uint16_t addr);
};

extern SMPDebugger smpDebugger;

#endif
