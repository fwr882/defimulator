#ifndef DEFIMULATOR_UI_DEBUGGER_BREAKPOINTEDITOR_H
#define DEFIMULATOR_UI_DEBUGGER_BREAKPOINTEDITOR_H

#include <ui/base.hpp>

struct BreakpointEditor : TopLevelWindow {
    enum : unsigned {
        Breakpoints = SNES::Debugger::Breakpoints
    };

    CheckBox runToBreakpoint;
    CheckBox enableBox[Breakpoints];
    TextBox addressBox[Breakpoints];
    TextBox valueBox[Breakpoints];
    ComboBox typeBox[Breakpoints];
    ComboBox sourceBox[Breakpoints];

    void create(void);
    void toggleBreakpoint(unsigned breakpoint);
    void eventBreakpoint(void);
};

extern BreakpointEditor breakpointEditor;

#endif
