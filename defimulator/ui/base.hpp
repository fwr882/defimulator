#ifndef BSNES_UI_BASE_H
#define BSNES_UI_BASE_H

#include <snes/snes.hpp>

#include <nall/base64.hpp>
#include <nall/config.hpp>
#include <nall/directory.hpp>
#include <nall/filemap.hpp>
#include <nall/input.hpp>
#include <nall/ups.hpp>
#include <nall/snes/cartridge.hpp>
#include <nall/gameboy/cartridge.hpp>
using namespace nall;

#include <ruby/ruby.hpp>
using namespace ruby;

#include <phoenix/phoenix.hpp>
using namespace phoenix;

struct TopLevelWindow : Window {
  string name;
  string position;
};

#include "interface.h"
#include "config.h"
#include "file-browser.h"
#include "main-window.h"
#include "slot-loader.h"
#include "settings.h"
#include "cheat-editor.h"
#include "state-manager.h"
#include "input.h"
#include "utility.h"
#include "cartridge.h"

#if defined(DEBUGGER)
  #include "debugger/debugger.hpp"
#endif

struct Application {
    Font proportionalFont;
    Font proportionalFontBold;
    Font monospaceFont;

    bool pause;
    bool quit;

    /* XXX: Weird... */
    void main(int argc, char **argv);

    void addWindow(TopLevelWindow *window, const string &name,
        const string &position);
    Application(void);

private:
    array<TopLevelWindow*> windows;
    configuration geometryConfig;
    void loadGeometry(void);
    void saveGeometry(void);
};

extern Application application;

struct Style {
    enum : unsigned {
        #if defined(PHOENIX_WINDOWS)
        ButtonHeight = 25,
        CheckBoxHeight = 15,
        ComboBoxHeight = 22,
        EditBoxHeight = 22,
        LabelHeight = 15,
        SliderHeight = 25,
        TextBoxHeight = 22,
        #elif defined(PHOENIX_GTK)
        ButtonHeight = 25,
        CheckBoxHeight = 15,
        ComboBoxHeight = 22,
        EditBoxHeight = 22,
        LabelHeight = 15,
        SliderHeight = 22,
        TextBoxHeight = 22,
        #elif defined(PHOENIX_QT)
        ButtonHeight = 25,
        CheckBoxHeight = 15,
        ComboBoxHeight = 22,
        EditBoxHeight = 22,
        LabelHeight = 15,
        SliderHeight = 22,
        TextBoxHeight = 22,
        #endif
    };
};

#endif
