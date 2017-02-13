#ifdef LCD_CPP

uint8 LCD::mmio_read(uint16 addr)
{
    if (addr >= 0x8000 && addr <= 0x9fff) {
        return vram[addr & 0x1fff];
    }

    if (addr >= 0xfe00 && addr <= 0xfe9f) {
        return oam[addr & 0xff];
    }

    /* LCDC */
    if(addr == 0xff40) {
        return (status.display_enable << 7)
             | (status.window_tilemap_select << 6)
             | (status.window_display_enable << 5)
             | (status.bg_tiledata_select << 4)
             | (status.bg_tilemap_select << 3)
             | (status.obj_size << 2)
             | (status.obj_enable << 1)
             | (status.bg_enable << 0);
    }

    /* STAT */
    if (addr == 0xff41) {
        unsigned mode;
        if (status.ly >= 144) {
            /* VBlank */
            mode = 1;
        } else if (status.lx >= 320) {
            /* HBlank */
            mode = 0;
        } else {
            /* LCD transfer */
            mode = 3;
        }

        return (status.interrupt_lyc << 6)
             | (status.interrupt_oam << 5)
             | (status.interrupt_vblank << 4)
             | (status.interrupt_hblank << 3)
             | ((status.ly == status.lyc) << 2)
             | (mode << 0);
    }

    /* SCY */
    if (addr == 0xff42) {
        return status.scy;
    }

    /* SCX */
    if (addr == 0xff43) {
        return status.scx;
    }

    /* LY */
    if (addr == 0xff44) {
        return status.ly;
    }

    /* LYC */
    if (addr == 0xff45) {
        return status.lyc;
    }

    /* BGP */
    if (addr == 0xff47) {
        return (status.bgp[3] << 6)
             | (status.bgp[2] << 4)
             | (status.bgp[1] << 2)
             | (status.bgp[0] << 0);
    }

    /* OBPO */
    if (addr == 0xff48) {
        return (status.obp[0][3] << 6)
             | (status.obp[0][2] << 4)
             | (status.obp[0][1] << 2)
             | (status.obp[0][0] << 0);
    }

    /* OBP1 */
    if (addr == 0xff49) {
        return (status.obp[1][3] << 6)
             | (status.obp[1][2] << 4)
             | (status.obp[1][1] << 2)
             | (status.obp[1][0] << 0);
    }

    /* WY */
    if (addr == 0xff4a) {
        return status.wy;
    }

    /* WX */
    if (addr == 0xff4b) {
        return status.wx;
    }

    return 0x00;
}

void LCD::mmio_write(uint16 addr, uint8 data)
{
    if (addr >= 0x8000 && addr <= 0x9fff) {
        vram[addr & 0x1fff] = data;
        return;
    }

    if (addr >= 0xfe00 && addr <= 0xfe9f) {
        oam[addr & 0xff] = data;
        return;
    }

    /* LCDC */
    if (addr == 0xff40) {
        status.display_enable = data & 0x80;
        status.window_tilemap_select = data & 0x40;
        status.window_display_enable = data & 0x20;
        status.bg_tiledata_select = data & 0x10;
        status.bg_tilemap_select = data & 0x08;
        status.obj_size = data & 0x04;
        status.obj_enable = data & 0x02;
        status.bg_enable = data & 0x01;
        return;
    }

    /* STAT */
    if (addr == 0xff41) {
        status.interrupt_lyc = data & 0x40;
        status.interrupt_oam = data & 0x20;
        status.interrupt_vblank = data & 0x10;
        status.interrupt_hblank = data & 0x08;
        return;
    }

    /* SCY */
    if (addr == 0xff42) {
        status.scy = data;
        return;
    }

    /* SCX */
    if (addr == 0xff43) {
        status.scx = data;
        return;
    }

    /* LY */
    if (addr == 0xff44) {
        status.ly = 0;
        return;
    }

    /* LYC */
    if (addr == 0xff45) {
        status.lyc = data;
        return;
    }

    /* DMA */
    if (addr == 0xff46) {
        for (unsigned n = 0x00; n <= 0x9f; n++) {
            bus.write(0xfe00 + n, bus.read((data << 8) + n));
        }
        return;
    }

    /* BGP */
    if (addr == 0xff47) {
        status.bgp[3] = (data >> 6) & 3;
        status.bgp[2] = (data >> 4) & 3;
        status.bgp[1] = (data >> 2) & 3;
        status.bgp[0] = (data >> 0) & 3;
        return;
    }

    /* OBPO */
    if (addr == 0xff48) {
        status.obp[0][3] = (data >> 6) & 3;
        status.obp[0][2] = (data >> 4) & 3;
        status.obp[0][1] = (data >> 2) & 3;
        status.obp[0][0] = (data >> 0) & 3;
        return;
    }

    /* OBP1 */
    if (addr == 0xff49) {
        status.obp[1][3] = (data >> 6) & 3;
        status.obp[1][2] = (data >> 4) & 3;
        status.obp[1][1] = (data >> 2) & 3;
        status.obp[1][0] = (data >> 0) & 3;
        return;
    }

    /* WY */
    if (addr == 0xff4a) {
        status.wy = data;
        return;
    }

    /* WX */
    if (addr == 0xff4b) {
        status.wx = data;
        return;
    }
}

#endif
