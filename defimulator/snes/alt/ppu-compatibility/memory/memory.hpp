#ifndef DEFIMULATOR_SNES_ALT_PPUCOMPATIBILITY_MEMORY_H
#define DEFIMULATOR_SNES_ALT_PPUCOMPATIBILITY_MEMORY_H

uint16 get_vram_address(void);

debugvirtual uint8 vram_mmio_read(uint16 addr);
debugvirtual void vram_mmio_write(uint16 addr, uint8 data);

debugvirtual uint8 oam_mmio_read(uint16 addr);
debugvirtual void oam_mmio_write(uint16 addr, uint8 data);

debugvirtual uint8 cgram_mmio_read(uint16 addr);
debugvirtual void cgram_mmio_write(uint16 addr, uint8 data);

#endif
