project(bsnes CXX)
enable_language(C)

include_directories("${bsnes_SOURCE_DIR}")
include_directories("${GTK2_INCLUDE_DIRS}")

# TODO: Tweaked with available profiles from initial config.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPHOENIX_GTK")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fomit-frame-pointer")
# Audio/Video backends for ruby
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVIDEO_SDL")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVIDEO_GLX")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVIDEO_XV")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAUDIO_AO")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DINPUT_SDL")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fomit-frame-pointer")

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

list(APPEND sources
    ui/main.cpp
    ui/general/general.cpp
    ui/settings/settings.cpp
    ui/tools/tools.cpp
    ui/input/input.cpp
    ui/utility/utility.cpp
    ui/cartridge/cartridge.cpp
    ui/debugger/debugger.cpp
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
    ${X11_LIBRARIES}
    ${XV_LIBRARIES}
    ${XEXT_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GTK2_LIBRARIES}
    ${SDL_LIBRARIES}
    ${AO_LIBRARIES}
    ${CMAKE_DL_LIBS}
)
