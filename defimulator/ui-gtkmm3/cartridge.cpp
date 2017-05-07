#include "cartridge.h"

/*
* TODO: Should this be overloaded instead of being able to pass
* nullptrs around?  Would make setting the internal names a little
* safer I think.
*/
bool Cartridge::load(Cartridge::Type type, const char* base,
    const char* slot_a, const char* slot_b)
{
    this->unload();
    if (this->load_cartridge(SNES::memory::cartrom, m_basexml,
        base) == false) {
        return false;
    }

    m_type = type;
    SNES::cartridge.basename = m_basename = nall::basename(base);
    if (slot_a) {
        m_slotaname = nall::basename(slot_a);
    }

    if (slot_b) {
        m_slotbname = nall::basename(slot_b);
    }

    /* Only used for loading SuperGameBoy roms */
    nall::file fp;
    unsigned size;
    uint8_t* data = nullptr;
    GameBoyCartridge* info = nullptr;

    switch (m_type) {
    case Cartridge::STANDARD:
        SNES::cartridge.load(SNES::Cartridge::Mode::Normal, { m_basexml });
        this->load_memory(SNES::memory::cartram, m_basename, ".srm");
        this->load_memory(SNES::memory::cartrtc, m_basename, ".rtc");
        break;
    case Cartridge::BSX:
        this->load_cartridge(SNES::memory::bsxflash, m_slotaxml, slot_a);
        SNES::cartridge.load(SNES::Cartridge::Mode::Bsx,
            { m_basexml, m_slotaxml });
        this->load_memory(SNES::memory::bsxram, m_basename, ".srm");
        this->load_memory(SNES::memory::bsxpram, m_basename, ".psr");
        break;
    case Cartridge::BSX_SLOTTED:
        /* XXX: So what if this call to load_cartridge fails? */
        this->load_cartridge(SNES::memory::bsxflash, m_slotaxml, slot_a);
        SNES::cartridge.basename = m_basename = nall::basename(base);
        SNES::cartridge.load(SNES::Cartridge::Mode::BsxSlotted,
            { m_basexml, m_slotaxml });
        this->load_memory(SNES::memory::cartram, m_basename, ".srm");
        this->load_memory(SNES::memory::cartrtc, m_basename, ".rtc");
        break;
    case Cartridge::SUFAMI_TURBO:
        this->load_cartridge(SNES::memory::stArom, m_slotaxml, slot_a);
        this->load_cartridge(SNES::memory::stBrom, m_slotbxml, slot_b);
        SNES::cartridge.load(SNES::Cartridge::Mode::SufamiTurbo,
            { m_basexml, m_slotaxml, m_slotbxml });
        this->load_memory(SNES::memory::stAram, m_slotaname, ".srm");
        this->load_memory(SNES::memory::stBram, m_slotbname, ".srm");
        break;
    case Cartridge::SUPER_GAME_BOY:
        if (fp.open(slot_a, nall::file::mode::read)) {
            size = fp.size();
            data = new uint8_t[size];
            fp.read(data, size);
            fp.close();

            info = new GameBoyCartridge(data, size);
            GameBoy::cartridge.load(info->xml, data, size);

            delete(info);
            delete[] data;
        } else {
            return false;
        }

        SNES::cartridge.load(SNES::Cartridge::Mode::SuperGameBoy,
            { m_basexml, "" });

        if (GameBoy::cartridge.info.battery &&
            fp.open(nall::string(m_slotaname, ".sav"), file::mode::read)) {
            fp.read(GameBoy::cartridge.ramdata,
                min(GameBoy::cartridge.ramsize, fp.size()));
            fp.close();
        }

        break;
    default:
        return false;
    }

    return true;
}

bool Cartridge::unload(void)
{
    m_patched = false;
    if (SNES::cartridge.loaded() == false) {
        return false;
    }

    /*
    * TODO: Put this in the home directory, not the ROM directory.
    */
    this->save_memory(SNES::memory::cartram, m_basename, ".srm");
    this->save_memory(SNES::memory::cartrtc, m_basename, ".rtc");
    this->save_memory(SNES::memory::bsxram, m_basename, ".srm");
    this->save_memory(SNES::memory::bsxpram, m_basename, ".psr");
    this->save_memory(SNES::memory::stAram, m_slotaname, ".srm");
    this->save_memory(SNES::memory::stBram, m_slotbname, ".srm");

    if (SNES::cartridge.mode() == SNES::Cartridge::Mode::SuperGameBoy) {
        nall::file fp;
        if (GameBoy::cartridge.info.battery &&
            fp.open(nall::string(m_slotaname, ".sav"),
                nall::file::mode::write)) {
            fp.write(GameBoy::cartridge.ramdata,
                GameBoy::cartridge.ramsize);
            fp.close();
        }
    }

    m_basename = m_slotaname = m_slotbname = "";

    return true;
}

/*
* Private function definitions
*/
bool Cartridge::load_cartridge(SNES::MappedRAM &memory, nall::string &XML,
    const char* filename)
{
    if (nall::file::exists(filename) == false) {
        return false;
    }

    nall::file fp;
    if (fp.open(filename, file::mode::read) == false) {
        return false;
    }

    if (XML.readfile(nall::string(nall::basename(filename),
        ".xml")) == false) {
        XML = "";
    }

    unsigned size = fp.size();
    uint8_t* data = new uint8_t[size];

    fp.read(data, size);
    fp.close();

    nall::filemap patch(nall::string(nall::basename(filename), ".ups"),
        nall::filemap::mode::read);
    if (patch.opened()) {
        unsigned targetsize;
        nall::ups patcher;
        if (patcher.apply(patch.data(), patch.size(), data, size, nullptr,
            targetsize) == nall::ups::result::target_too_small) {
            uint8_t* targetdata = new uint8_t[targetsize];
            if (patcher.apply(patch.data(), patch.size(), data, size,
                targetdata, targetsize) == nall::ups::result::success) {
                delete[](data);
                data = targetdata;
                size = targetsize;
                m_patched = true;
            }
        }
    }

    if (XML == "") {
        XML = SNESCartridge(data, size).xmlMemoryMap;
    }

    /* where is this 'memory' object? */
    memory.copy(data, size);
    delete[](data);

    return true;
}

bool Cartridge::load_memory(SNES::MappedRAM &memory, nall::string filename,
    const char* extension)
{
    if (memory.size() == 0 || memory.size() == ~0) {
        return true;
    }

    filename = { filename, extension };
    if (nall::file::exists(filename) == false) {
        return false;
    }

    nall::file fp;
    if (fp.open(filename, nall::file::mode::read)) {
        fp.read(memory.data(), min(memory.size(), fp.size()));
        fp.close();
    }

    return true;
}

bool Cartridge::save_memory(SNES::MappedRAM &memory, nall::string filename,
    const char* extension)
{
    if (memory.size() == 0 || memory.size() == ~0) {
        return true;
    }

    filename = { filename, extension };
    nall::file fp;
    if (fp.open(filename, nall::file::mode::write) == false) {
        return false;
    }

    fp.write(memory.data(), memory.size());
    fp.close();

    return true;
}
