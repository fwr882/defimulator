#ifndef DEFIMULATOR_UI_DEBUGGER_MEMORYEDITOR_H
#define DEFIMULATOR_UI_DEBUGGER_MEMORYEDITOR_H

#include <ui/base.hpp>

struct MemoryEditor : TopLevelWindow {
    HexEditor editor;
    ComboBox sourceBox;
    TextBox gotoBox;
    Button refreshButton;

    SNES::Debugger::MemorySource source;
    unsigned size;

    void create(void);
    void setSource(SNES::Debugger::MemorySource source);
    uint8_t read(unsigned addr);
    void write(unsigned addr, uint8_t data);
};

extern MemoryEditor memoryEditor;

#endif
