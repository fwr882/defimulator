#ifndef DEFIMULATOR_UI_INPUT_H
#define DEFIMULATOR_UI_INPUT_H

#include <ui/base.hpp>

struct InputMapper {
    struct AbstractInput {
        enum class Type : unsigned {
            Button,
            MouseAxis,
            MouseButton,
            HatUp,
            HatDown,
            HatLeft,
            HatRight,
            AxisLo,
            AxisHi
        } type;

        string name;
        string mapping;
        unsigned scancode;
        virtual void bind(void);
    };

    struct AnalogInput : AbstractInput {
        int16_t poll(void);
    };

    struct DigitalInput : AbstractInput {
        int16_t poll(void);
    };

    struct Controller : array<AbstractInput*> {
        string name;
    };

    struct Hotkeys : Controller {
        /* save state, load state, next save slot, previous save slot */
        DigitalInput save, load, nextstate, prevstate;
        /* fast-forward emulation, pause emulation, unaquire input */
        DigitalInput fastforward, pause, unaquire;

        void create(const char *deviceName, const char *configName);
    };

    struct Gamepad : Controller {
        DigitalInput up, down, left, right;
        DigitalInput b, a, y, x;
        DigitalInput l, r, select, start;
        void create(const char *deviceName, const char *configName);
        int16_t poll(unsigned id);
    };

    struct Mouse : Controller {
        AnalogInput x, y;
        DigitalInput left, right;
        void create(const char *deviceName, const char *configName);
        int16_t poll(unsigned id);
    };

    struct SuperScope : Controller {
        AnalogInput x, y;
        DigitalInput trigger, cursor, turbo, pause;
        void create(const char *deviceName, const char *configName);
        int16_t poll(unsigned id);
    };

    struct Justifier : Controller {
        AnalogInput x, y;
        DigitalInput trigger, start;
        void create(const char *deviceName, const char *configName);
        int16_t poll(unsigned id);
    };

    struct ControllerPort : array<Controller*> {
        string name;
    };

    struct Port1 : ControllerPort {
        Gamepad gamepad;
        Hotkeys hotkeys;
        Gamepad multitapA;
        Gamepad multitapB;
        Gamepad multitapC;
        Gamepad multitapD;
        Mouse mouse;
    } port1;

    struct Port2 : ControllerPort {
        Gamepad gamepad;
        Gamepad multitapA;
        Gamepad multitapB;
        Gamepad multitapC;
        Gamepad multitapD;
        Mouse mouse;
        SuperScope superScope;
        Justifier justifierA;
        Justifier justifierB;
    } port2;

    int16_t state[2][Scancode::Limit];
    bool activeState;

    void create(void);
    void bind(void);
    void poll(void);
    int16_t poll(bool port, SNES::Input::Device device,
        unsigned index, unsigned id);
    void poll_hotkeys(unsigned scancode, int16_t value);
    int16_t value(unsigned scancode);
};

extern InputMapper inputMapper;

#endif
