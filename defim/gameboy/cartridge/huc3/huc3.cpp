#ifdef CARTRIDGE_CPP

uint8 Cartridge::HuC3::mmio_read(uint16 addr)
{
    /* 0000 - 3FFF */
    if ((addr & 0xc000) == 0x0000) {
        return cartridge.rom_read(addr);
    }

    /* 4000 - 7FFF */
    if ((addr & 0xc000) == 0x4000) {  //4000-7fff
        return cartridge.rom_read((rom_select << 14) | (addr & 0x3fff));
    }

    /* A000 - BFFF */
    if ((addr & 0xe000) == 0xa000) {
        if (ram_enable) {
            return cartridge.ram_read((ram_select << 13) | (addr & 0x1fff));
        }
        return 0x00;
    }

    return 0x00;
}

void Cartridge::HuC3::mmio_write(uint16 addr, uint8 data)
{
    /* 0000 - 1FFF */
    if ((addr & 0xe000) == 0x0000) {
        ram_enable = ((data & 0x0f) == 0x0a);
        return;
    }

    /* 2000 - 3FFF */
    if ((addr & 0xe000) == 0x2000) {
        rom_select = data;
        return;
    }

    /* 4000 - 5FFF */
    if ((addr & 0xe000) == 0x4000) {
        ram_select = data;
        return;
    }

    /* 6000 - 7FFF; unknown purpose */
    if ((addr & 0xe000) == 0x6000) {
        return;
    }

    /* A000 - BFFF */
    if ((addr & 0xe000) == 0xa000) {
        if (ram_enable) {
            cartridge.ram_write((ram_select << 13) | (addr & 0x1fff), data);
        }
        return;
    }
}

void Cartridge::HuC3::power(void)
{
    ram_enable = false;
    rom_select = 0x01;
    ram_select = 0x00;
}

#endif
