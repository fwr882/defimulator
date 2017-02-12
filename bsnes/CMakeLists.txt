project(bsnes CXX)
enable_language(C)

include_directories("${bsnes_SOURCE_DIR}")
include_directories("${GTK2_INCLUDE_DIRS}")

# TODO: Tweaked with available profiles from initial config.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fomit-frame-pointer")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fomit-frame-pointer")

# GUI flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPHOENIX_GTK")

# Video Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVIDEO_SDL")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVIDEO_GLX")

# Audio Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAUDIO_AO")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAUDIO_ALSA")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAUDIO_PULSE")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DINPUT_SDL")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DINPUT_X")

if(EMULATION_PROFILE STREQUAL "ACCURACY")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPROFILE_ACCURACY")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPROFILE_ACCURACY")
elseif(EMULATION_PROFILE STREQUAL "PERFORMANCE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPROFILE_PERFORMANCE")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPROFILE_PERFORMANCE")
elseif(EMULATION_PROFILE STREQUAL "COMPATIBILITY")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPROFILE_COMPATIBILITY")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPROFILE_COMPATIBILITY")
endif()

if(BUILD_DEBUGGER)
    if(EMULATION_PROFILE STREQUAL "PERFORMANCE")
        message(FATAL_ERROR "** Cannot build debugger in PERFORMANCE profile.")
    else()
        message(">>>> Building debugger.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUGGER")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUGGER")
        list(APPEND sources ui/debugger/debugger.cpp)
    endif()
endif()

# Doesn't work.  But I'm sure this has something to do with it.
if(BUILD_GAMEBOY)
    list(APPEND sources
        ui-gameboy/main.cpp
        ui-gameboy/general/main-window.cpp
        ui-gameboy/utility/utility.cpp
    )
endif()

list(APPEND sources
    ui/main.cpp
    ui/general/general.cpp
    ui/settings/settings.cpp
    ui/tools/tools.cpp
    ui/input/input.cpp
    ui/utility/utility.cpp
    ui/cartridge/cartridge.cpp
    ruby/ruby.cpp
    phoenix/phoenix.cpp
    libco/libco.c
    snes/system/system.cpp
    snes/cartridge/cartridge.cpp
    snes/cheat/cheat.cpp
    snes/memory/memory.cpp
    snes/chip/icd2/icd2.cpp
    snes/chip/superfx/superfx.cpp
    snes/chip/sa1/sa1.cpp
    snes/chip/necdsp/necdsp.cpp
    snes/chip/bsx/bsx.cpp
    snes/chip/srtc/srtc.cpp
    snes/chip/sdd1/sdd1.cpp
    snes/chip/spc7110/spc7110.cpp
    snes/chip/cx4/cx4.cpp
    snes/chip/obc1/obc1.cpp
    snes/chip/st0018/st0018.cpp
    snes/chip/msu1/msu1.cpp
    snes/chip/serial/serial.cpp

    # XXX: Should these be consolidated in the gameboy build specifics?
    gameboy/system/system.cpp
    gameboy/scheduler/scheduler.cpp
    gameboy/memory/memory.cpp
    gameboy/cartridge/cartridge.cpp
    gameboy/cpu/cpu.cpp
    gameboy/lcd/lcd.cpp
)

if(EMULATION_PROFILE STREQUAL "ACCURACY")
    list(APPEND sources
        snes/cpu/core/core.cpp
        snes/smp/core/core.cpp
        snes/cpu/cpu.cpp
        snes/smp/smp.cpp
        snes/dsp/dsp.cpp
        snes/ppu/ppu.cpp
    )
elseif(EMULATION_PROFILE STREQUAL "COMPATIBILITY")
    list(APPEND sources
        snes/cpu/core/core.cpp
        snes/smp/core/core.cpp
        snes/cpu/cpu.cpp
        snes/smp/smp.cpp
        snes/alt/dsp/dsp.cpp
        snes/alt/ppu-compatibility/ppu.cpp
    )
elseif(EMULATION_PROFILE STREQUAL "PERFORMANCE")
    list(APPEND sources
        snes/cpu/core/core.cpp
        snes/smp/core/core.cpp
        snes/alt/cpu/cpu.cpp
        snes/smp/smp.cpp
        snes/alt/dsp/dsp.cpp
        snes/alt/ppu-performance/ppu.cpp
    )
endif()

add_executable(bsnes ${sources})

target_link_libraries(bsnes
    # Toolkit libraries
    ${GTK2_LIBRARIES}

    # Graphics Libraries
    ${OPENGL_LIBRARIES}
    ${SDL_LIBRARIES}
    ${X11_LIBRARIES}

    # Audio Libraries
    ${ALSA_LIBRARIES}
    ${AO_LIBRARIES}

    # For -ldl on *nix
    ${CMAKE_DL_LIBS}
)

if(BUILD_GAMEBOY)
    target_link_libraries(bsnes ${CURSES_LIBRARIES})
endif()
