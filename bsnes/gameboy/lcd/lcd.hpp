struct LCD : Processor, MMIO {
  #include "mmio/mmio.hpp"

  struct Status {
    unsigned lx;

    //$ff40  LCDC
    bool display_enable;
    bool window_tilemap_select;
    bool window_display_enable;
    bool bg_tiledata_select;
    bool bg_tilemap_select;
    bool obj_size;
    bool obj_enable;
    bool bg_enable;

    //$ff41  STAT
    bool interrupt_lyc;
    bool interrupt_oam;
    bool interrupt_vblank;
    bool interrupt_hblank;

    //$ff42  SCY
    uint8 scy;

    //$ff43  SCX
    uint8 scx;

    //$ff44  LY
    uint8 ly;

    //$ff45  LYC
    uint8 lyc;

    //$ff47  BGP
    uint8 bgp[4];

    //$ff48  OBP0
    //$ff49  OBP1
    uint8 obp[2][4];

    //$ff4a  WY
    uint8 wy;

    //$ff4b  WX
    uint8 wx;
  } status;

  uint8 screen[160 * 144];
  uint8 vram[8192];
  uint8 oam[160];
  uint8 line[160];

  static void Main();
  void main();
  void add_clocks(unsigned clocks);
  void scanline();
  void frame();
  void render();
  uint16 read_tile(bool select, unsigned x, unsigned y);
  void render_bg();
  void render_window();
  void render_obj();

  void power();

  void serialize(serializer&);
  LCD();
};

extern LCD lcd;
