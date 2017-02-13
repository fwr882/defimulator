#ifdef CARTRIDGE_CPP

uint8 Cartridge::MBC1::mmio_read(uint16 addr)
{
    /* 0000 - 3FFF */
    if ((addr & 0xc000) == 0x0000) {
        return cartridge.rom_read(addr);
    }

    /* 4000 - 7FFF */
    if ((addr & 0xc000) == 0x4000) {  //4000-7fff
        if (mode_select == 0) {
            return cartridge.rom_read(
                (ram_select << 19) | (rom_select << 14) | (addr & 0x3fff));
        } else {
            return cartridge.rom_read((rom_select << 14) | (addr & 0x3fff));
        }
    }

    /* A000 - BFFF */
    if ((addr & 0xe000) == 0xa000) {  //a000-bfff
        if (ram_enable) {
            if (mode_select == 0) {
                return cartridge.ram_read(addr & 0x1fff);
            } else {
                return cartridge.ram_read(
                    (ram_select << 13) | (addr & 0x1fff));
            }
        }
        return 0x00;
    }

    return 0x00;
}

void Cartridge::MBC1::mmio_write(uint16 addr, uint8 data)
{
    /* 0000 - 1FFF */
    if ((addr & 0xe000) == 0x0000) {
        ram_enable = (data & 0x0f) == 0x0a;
        return;
    }

    /* 2000 - 3FFF */
    if ((addr & 0xe000) == 0x2000) {
        rom_select = (data & 0x1f) + ((data & 0x1f) == 0);
        return;
    }

    /* 4000 - 5FFF */
    if ((addr & 0xe000) == 0x4000) {
        ram_select = data & 0x03;
        return;
    }

    /* 6000 - 7FFF */
    if ((addr & 0xe000) == 0x6000) {
        mode_select = data & 0x01;
        return;
    }

    /* A000 - BFFF */
    if ((addr & 0xe000) == 0xa000) {
        if (ram_enable) {
            if (mode_select == 0) {
                cartridge.ram_write(addr & 0x1fff, data);
            } else {
                cartridge.ram_write(
                    (ram_select << 13) | (addr & 0x1fff), data);
            }
        }
        return;
    }
}

void Cartridge::MBC1::power(void)
{
    ram_enable = false;
    rom_select = 0x01;
    ram_select = 0x00;
    mode_select = 0;
}

#endif
