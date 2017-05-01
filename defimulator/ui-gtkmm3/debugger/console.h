#ifndef DEFIMULATOR_UI_DEBUGGER_CONSOLE_H
#define DEFIMULATOR_UI_DEBUGGER_CONSOLE_H

#include <ui/base.hpp>

struct Console : TopLevelWindow {
    EditBox output;
    CheckBox traceToConsole;
    CheckBox traceToFile;
    CheckBox traceCPU;
    CheckBox traceSMP;
    Button clearConsole;

    string buffer;
    file logfile;

    void create(void);
    void write(const string &text, bool echo = false);
    void tracerEnable(bool state);
    void eventBreakpoint(void);
    void eventTraceCPU(void);
    void eventTraceSMP(void);
};

extern Console console;

#endif
