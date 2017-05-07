#ifndef DEFIMULATOR_UI_CARTRIDGE_H
#define DEFIMULATOR_UI_CARTRIDGE_H

#include <snes/snes.hpp>

#include <nall/file.hpp>
#include <nall/filemap.hpp>
#include <nall/string.hpp>
#include <nall/ups.hpp>
#include <nall/snes/cartridge.hpp>

class Cartridge {
public:
    enum Type {
        STANDARD,
        BSX,
        BSX_SLOTTED,
        SUFAMI_TURBO,
        SUPER_GAME_BOY
    } m_type;

    /*
    * TODO: I'd rather just have get() methods for these member object.
    * The Cartridge class should load these values and whatever is trying
    * to read the cartridge shouldn't be poking at the raw names and XML
    */
    nall::string m_basename, m_slotaname, m_slotbname;
    nall::string m_basexml, m_slotaxml, m_slotbxml;
    bool m_patched;

    bool load(Type type, const char* base, const char* slot_a,
        const char* slot_b);
    bool unload(void);
private:
    bool load_cartridge(SNES::MappedRAM &memory, nall::string &XML,
        const char* filename);
    bool load_memory(SNES::MappedRAM &memory, nall::string filename,
        const char* extension);
    bool save_memory(SNES::MappedRAM &memory, nall::string filename,
        const char* extension);
};

#endif
