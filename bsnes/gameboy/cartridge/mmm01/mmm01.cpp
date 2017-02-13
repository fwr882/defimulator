#ifdef CARTRIDGE_CPP

uint8 Cartridge::MMM01::mmio_read(uint16 addr)
{
    if ((addr & 0x8000) == 0x0000) {
        if(rom_mode == 0) return cartridge.rom_read(addr);
    }

    if ((addr & 0xc000) == 0x0000) {
        return cartridge.rom_read(0x8000 + (rom_base << 14) + (addr & 0x3fff));
    }

    if ((addr & 0xc000) == 0x4000) {
        return cartridge.rom_read(0x8000 + (rom_base << 14) +
            (rom_select << 14) + (addr & 0x3fff));
    }

    if ((addr & 0xe000) == 0xa000) {
        if (ram_enable) {
            return cartridge.ram_read((ram_select << 13) + (addr & 0x1fff));
        }
        return 0x00;
    }

    return 0x00;
}

void Cartridge::MMM01::mmio_write(uint16 addr, uint8 data)
{
    /* 0000 - 1FFF */
    if ((addr & 0xe000) == 0x0000) {
        if (rom_mode == 0) {
            rom_mode = 1;
        } else {
            ram_enable = ((data & 0x0f) == 0x0a);
        }
    }

    /* 2000 - 3FFF */
    if ((addr & 0xe000) == 0x2000) {
        if (rom_mode == 0) {
            rom_base = data & 0x3f;
        } else {
            rom_select = data;
        }
    }

    /* 4000 - 5FFF */
    if ((addr & 0xe000) == 0x4000) {
        if (rom_mode == 1) {
            ram_select = data;
        }
    }

    /* Uknown purpose; 6000 - 7FFF */
    if ((addr & 0xe000) == 0x6000) { }

    /* A000 - BFFF */
    if ((addr & 0xe000) == 0xa000) {
        if (ram_enable) {
            cartridge.ram_write((ram_select << 13) + (addr & 0x1fff), data);
        }
    }
}

void Cartridge::MMM01::power(void)
{
    rom_mode = 0;
    rom_base = 0x00;

    ram_enable = false;
    rom_select = 0x01;
    ram_select = 0x00;
}

#endif
