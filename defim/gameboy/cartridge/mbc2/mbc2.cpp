#ifdef CARTRIDGE_CPP

uint8 Cartridge::MBC2::mmio_read(uint16 addr)
{
    if ((addr & 0xc000) == 0x0000) {  //0000-3fff
        return cartridge.rom_read(addr);
    }

    if ((addr & 0xc000) == 0x4000) {  //4000-7fff
        return cartridge.rom_read((rom_select << 14) | (addr & 0x3fff));
    }

    if ((addr & 0xfe00) == 0xa000) {  //a000-a1ff
        if (ram_enable) {
            return cartridge.ram_read(addr & 0x1ff);
        }
        return 0x00;
    }

    return 0x00;
}

void Cartridge::MBC2::mmio_write(uint16 addr, uint8 data)
{
    /* 0000 - 1FFF [d8=0] */
    if ((addr & 0xe100) == 0x0000) {
        ram_enable = (data & 0x0f) == 0x0a;
        return;
    }

    /* 2000 - 3FFF [d8=1] */
    if ((addr & 0xe100) == 0x2100) {
        rom_select = (data & 0x0f) + ((data & 0x0f) == 0);
        return;
    }

    if ((addr & 0xfe00) == 0xa000) {  //a000-a1ff
        if (ram_enable) {
            cartridge.ram_write(addr & 0x1ff, data & 0x0f);
        }
        return;
    }
}

void Cartridge::MBC2::power(void)
{
    ram_enable = false;
    rom_select = 0x01;
}

#endif
