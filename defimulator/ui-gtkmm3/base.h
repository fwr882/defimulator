#ifndef DEFIMULATOR_UI_BASE_H
#define DEFIMULATOR_UI_BASE_H

#include <snes/snes.hpp>
#include <ruby/ruby.hpp>

struct state_t {
    bool focused;
    bool pause;
    bool quit;
};

#endif
