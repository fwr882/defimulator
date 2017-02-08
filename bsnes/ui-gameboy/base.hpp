#include <nall/file.hpp>
#include <nall/foreach.hpp>
#include <nall/stdint.hpp>
#include <nall/string.hpp>
#include <nall/gameboy/cartridge.hpp>
using namespace nall;

#include <ruby/ruby.hpp>
using namespace ruby;

#include <phoenix/phoenix.hpp>
using namespace phoenix;

#include <gameboy/gameboy.hpp>

#include "interface.hpp"

#include "general/main-window.hpp"

#include "utility/utility.hpp"

struct Application {
  bool quit;

  Font proportionalFont;
  Font proportionalFontBold;
  Font monospaceFont;

  void main(int argc, char **argv);
};

extern Application application;
