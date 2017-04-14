#ifndef DEFIMULATOR_SNES_CHIP_SA1_DMA_H
#define DEFIMULATOR_SNES_CHIP_SA1_DMA_H

struct DMA {
    enum CDEN {
        DmaNormal = 0,
        DmaCharConversion = 1
    };

    enum SD {
        SourceROM = 0,
        SourceBWRAM = 1,
        SourceIRAM = 2
    };

    enum DD {
        DestIRAM = 0,
        DestBWRAM = 1
    };

    unsigned line;
} dma;

void dma_normal(void);
void dma_cc1(void);
uint8 dma_cc1_read(unsigned addr);
void dma_cc2(void);

#endif
