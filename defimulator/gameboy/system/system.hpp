class Interface;

enum class Input : unsigned {
    Up,
    Down,
    Left,
    Right,
    B,
    A,
    Select,
    Start,
};

struct System : MMIO {
    struct BootROM {
        static const uint8 dmg[256];
        static const uint8 sgb[256];
    } bootROM;

    void run(void);
    void runtosave(void);
    void runthreadtosave(void);

    uint8 mmio_read(uint16 addr);
    void mmio_write(uint16 addr, uint8 data);

    void init(Interface*);
    void power(void);

    Interface *interface;
    unsigned clocks_executed;

    /* serialization.cpp */
    unsigned serialize_size;

    serializer serialize(void);
    bool unserialize(serializer&);

    void serialize(serializer&);
    void serialize_all(serializer&);
    void serialize_init(void);
};

#include <gameboy/interface/interface.hpp>

extern System system;
