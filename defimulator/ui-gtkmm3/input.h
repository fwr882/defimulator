#ifndef DEFIMULATOR_UI_INPUT_H
#define DEFIMULATOR_UI_INPUT_H

#include <memory>

#include <nall/array.hpp>
#include <nall/input.hpp>
#include <nall/string.hpp>

#include <ui-gtkmm3/base.h>
#include <ui-gtkmm3/configuration.h>

class InputMapper {
public:
    struct AbstractInput {
        enum Type {
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

        nall::string name;
        nall::string mapping;
        unsigned scancode;
        virtual void bind(void);
    };

    struct AnalogInput : AbstractInput {
        int16_t poll(InputMapper inputMapper);
        //int16_t poll(void);
    };

    struct DigitalInput : AbstractInput {
        int16_t poll(InputMapper inputMapper);
        //int16_t poll(void);
    };

    struct Controller : nall::array<AbstractInput*> {
        nall::string name;
    };

    struct Hotkeys : Controller {
        DigitalInput save, load, nextstate, prevstate;
        DigitalInput fastforward, pause;
        void create(Configuration* config, const char* deviceName,
            const char* configName);
    };

    struct Gamepad : Controller {
        DigitalInput up, down, left, right;
        DigitalInput b, a, y, x;
        DigitalInput l, r, select, start;
        void create(Configuration* config, const char* deviceName,
            const char* configName);
        int16_t poll(unsigned id);
    };

    struct Mouse : Controller {
        AnalogInput x, y;
        DigitalInput left, right;
        void create(Configuration* config, const char* deviceName,
            const char* configName);
        int16_t poll(unsigned id);
    };

    struct SuperScope : Controller {
        AnalogInput x, y;
        DigitalInput trigger, cursor, turbo, pause;
        void create(Configuration* config, const char* deviceName,
            const char* configName);
        int16_t poll(unsigned id);
    };

    struct Justifier : Controller {
        AnalogInput x, y;
        DigitalInput trigger, start;
        void create(Configuration* config, const char* deviceName,
            const char* configName);
        int16_t poll(unsigned id);
    };

    struct ControllerPort : nall::array<Controller*> {
        nall::string name;
    };

    struct Port1 : nall::array<Controller*> {
        Gamepad gamepad;
        Hotkeys hotkeys;
        Gamepad multitapA;
        Gamepad multitapB;
        Gamepad multitapC;
        Gamepad multitapD;
        Mouse mouse;
    } port1;

    struct Port2 : nall::array<Controller*> {
        Gamepad gamepad;
        Gamepad multitapA;
        Gamepad multitapB;
        Gamepad multitapC;
        Gamepad multitapD;
        Mouse mouse;
        Justifier justifierA;
        Justifier justifierB;
    } port2;

    int16_t state[2][nall::Scancode::Limit];
    bool activeState;
    std::shared_ptr<state_t> m_state;

    void create(std::shared_ptr<state_t> state, Configuration* config);
    void bind(void);
    void poll(Configuration* config);
    int16_t poll(bool port, SNES::Input::Device device, unsigned index,
        unsigned id);
    void poll_hotkeys(Configuration* config, unsigned scancode,
        int16_t value);
    int16_t value(unsigned scancode);
};

#endif
