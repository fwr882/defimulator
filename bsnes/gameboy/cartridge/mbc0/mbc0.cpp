#ifdef CARTRIDGE_CPP

uint8 Cartridge::MBC0::mmio_read(uint16 addr)
{
    /* 0000 - 7FFF */
    if ((addr & 0x8000) == 0x0000) {
        return cartridge.rom_read(addr);
    }

    /* A000 - BFFF */
    if ((addr & 0xe000) == 0xa000) {
        return cartridge.ram_read(addr & 0x1fff);
    }

    return 0x00;
}

void Cartridge::MBC0::mmio_write(uint16 addr, uint8 data)
{
    /* A000 - BFFF */
    if ((addr & 0xe000) == 0xa000) {
        cartridge.ram_write(addr & 0x1fff, data);
        return;
    }
}

void Cartridge::MBC0::power(void) { }

#endif
