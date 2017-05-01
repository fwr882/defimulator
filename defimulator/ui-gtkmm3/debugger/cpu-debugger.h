#ifndef DEFIMULATOR_UI_DEBUGGER_CPUDEBUGGER_H
#define DEFIMULATOR_UI_DEBUGGER_CPUDEBUGGER_H

#include <ui/base.hpp>
#include <ui/debugger/console.h>

struct CPUDebugger : TopLevelWindow {
    EditBox output;
    Button stepInto;
    Button stepOver;
    Button proceed;

    void create(void);
    void synchronize(void);
    void refreshDisassembly(void);
    void eventStepInto(void);
    void eventStepOver(void);

    uint8_t read(unsigned addr);
};

extern CPUDebugger cpuDebugger;


#endif
