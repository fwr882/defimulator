#ifdef SYSTEM_CPP

Video video;

const uint8_t Video::cursor[15 * 15] = {
    0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
    0,0,0,0,1,1,2,2,2,1,1,0,0,0,0,
    0,0,0,1,2,2,1,2,1,2,2,1,0,0,0,
    0,0,1,2,1,1,0,1,0,1,1,2,1,0,0,
    0,1,2,1,0,0,0,1,0,0,0,1,2,1,0,
    0,1,2,1,0,0,1,2,1,0,0,1,2,1,0,
    1,2,1,0,0,1,1,2,1,1,0,0,1,2,1,
    1,2,2,1,1,2,2,2,2,2,1,1,2,2,1,
    1,2,1,0,0,1,1,2,1,1,0,0,1,2,1,
    0,1,2,1,0,0,1,2,1,0,0,1,2,1,0,
    0,1,2,1,0,0,0,1,0,0,0,1,2,1,0,
    0,0,1,2,1,1,0,1,0,1,1,2,1,0,0,
    0,0,0,1,2,2,1,2,1,2,2,1,0,0,0,
    0,0,0,0,1,1,2,2,2,1,1,0,0,0,0,
    0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
};

void Video::draw_cursor(uint16_t color, int x, int y)
{
    uint16_t *data = (uint16_t*)ppu.output;
    if (ppu.interlace() && ppu.field()) {
        data += 512;
    }

    for (int cy = 0; cy < 15; cy++) {
        int vy = y + cy - 7;
        /* do not draw offscreen */
        if (vy <= 0 || vy >= 240) {
            continue;
        }

        bool hires = (line_width[vy] == 512);
        for (int cx = 0; cx < 15; cx++) {
            int vx = x + cx - 7;

            /* do not draw offscreen */
            if (vx < 0 || vx >= 256) {
                continue;
            }

            uint8_t pixel = cursor[cy * 15 + cx];
            if (pixel == 0) {
                continue;
            }

            uint16_t pixelcolor = color;
            if (pixel == 1) {
                pixelcolor = 0;
            }

            if (hires == false) {
                *((uint16_t*)data + vy * 1024 + vx) = pixelcolor;
            } else {
                *((uint16_t*)data + vy * 1024 + vx * 2 + 0) = pixelcolor;
                *((uint16_t*)data + vy * 1024 + vx * 2 + 1) = pixelcolor;
            }
        }
    }
}

void Video::update(void)
{
    /* draw the cursor if we've got an aiming device. */
    switch (input.port[1].device) {
    case Input::Device::SuperScope:
        draw_cursor(0x001f, input.port[1].superscope.x,
            input.port[1].superscope.y);
        break;
    case Input::Device::Justifiers:
        draw_cursor(0x02e0, input.port[1].justifier.x2,
            input.port[1].justifier.y2);
        /* fallthrough */
    case Input::Device::Justifier:
        draw_cursor(0x001f, input.port[1].justifier.x1,
            input.port[1].justifier.y1);
        break;
    }

    uint16_t *data = (uint16_t*)ppu.output;
    if (ppu.interlace() && ppu.field()) {
        data += 512;
    }

    unsigned width = 256;
    unsigned height = 224;
    if (ppu.overscan()) {
        height = 239;
    }

    if (frame_hires) {
        width <<= 1;
        /* normalize line widths */
        for (unsigned y = 0; y < 240; y++) {
            if (line_width[y] == 512) {
                continue;
            }

            uint16_t *buffer = data + y * 1024;
            for (signed x = 255; x >= 0; x--) {
                buffer[(x * 2) + 0] = buffer[(x * 2) + 1] = buffer[x];
            }
        }
    }

    if (frame_interlace) {
        height <<= 1;
    }

    system.interface->video_refresh(ppu.output + 1024, width, height);

    frame_hires = false;
    frame_interlace = false;
}

void Video::scanline(void)
{
    unsigned y = cpu.vcounter();
    if (y >= 240) {
        return;
    }

    frame_hires |= ppu.hires();
    frame_interlace |= ppu.interlace();

    unsigned width = 512;
    if (ppu.hires() == false) {
        width = 256;
    }

    line_width[y] = width;
}

void Video::init(void)
{
    frame_hires = false;
    frame_interlace = false;
    for (unsigned i = 0; i < 240; i++) {
        line_width[i] = 256;
    }
}

#endif
