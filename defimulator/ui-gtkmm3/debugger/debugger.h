#ifndef DEFIMULATOR_UI_DEBUGGER_DEBUGGER_H
#define DEFIMULATOR_UI_DEBUGGER_DEBUGGER_H

#include <ui/debugger/console.h>
#include <ui/debugger/cpu-debugger.h>
#include <ui/debugger/smp-debugger.h>
#include <ui/debugger/breakpoint-editor.h>
#include <ui/debugger/memory-editor.h>

struct Debugger : TopLevelWindow {
    enum class DebugMode : unsigned {
        None,
        WaitForBreakpoint,
        StepIntoCPU,
        StepIntoSMP,
    } debugMode;

    CheckBox enableDebugger;
    CheckBox showConsole;
    CheckBox showCPUDebugger;
    CheckBox showSMPDebugger;
    CheckBox showBreakpointEditor;
    CheckBox showMemoryEditor;

    void create(void);
    void synchronize(void);
    void setVisible(bool visible = true);
    void enable(bool state);
    void run(void);
    bool step_cpu(void);
    bool step_smp(void);

    Debugger(void);
};

extern Debugger debugger;

#endif
