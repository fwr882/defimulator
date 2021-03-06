#ifndef DEFIMULATOR_UI_CARTRIDGE_H
#define DEFIMULATOR_UI_CARTRIDGE_H

#include <ui/base.hpp>

struct Cartridge {
    bool loadNormal(const char *basename);
    bool loadBsxSlotted(const char *basename, const char *slotname);
    bool loadBsx(const char *basename, const char *slotname);
    bool loadSufamiTurbo(const char *basename, const char *slotAname,
        const char *slotBname);
    bool loadSuperGameBoy(const char *basename, const char *slotname);
    void unload(void);

    string baseName, slotAName, slotBName;
    string baseXML, slotAXML, slotBXML;
    bool patchApplied;

private:
    bool loadCartridge(SNES::MappedRAM &memory, string &XML,
        const char *filename);
    bool loadMemory(SNES::MappedRAM &memory, string filename,
        const char *extension);
    bool saveMemory(SNES::MappedRAM &memory, string filename,
        const char *extension);
};

extern Cartridge cartridge;

#endif
