project(defim CXX)
enable_language(C)

include_directories("${defim_SOURCE_DIR}")

if(NOT WIN32)
    include_directories("${GTK2_INCLUDE_DIRS}")
endif()

# TODO: Tweaked with available profiles from initial config.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fomit-frame-pointer")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fomit-frame-pointer")

# GUI flag
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPHOENIX_WINDOWS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVIDEO_WGL")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAUDIO_DIRECTSOUND")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DINPUT_DIRECTINPUT")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPHOENIX_GTK")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVIDEO_GLX")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVIDEO_SDL")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DINPUT_SDL")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DINPUT_X")

    # OSS has not been in Linux for a while.  If on a UNIX platform,
    # use OSS.  If on Linux, use ALSA.  On MAC...no solution yet.
    if(NOT LINUX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAUDIO_OSS")
        message(">>>> Using OSS for sound.")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAUDIO_ALSA")
        message(">>>> Using ALSA for sound.")
    endif()
endif()


# Video Flags
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
        message("!!!! Cannot build debugger in PERFORMANCE profile.")
    else()
        message(">>>> Building debugger.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUGGER")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUGGER")
        list(APPEND sources
            ui/debugger/breakpoint-editor.cpp
            ui/debugger/console.cpp
            ui/debugger/cpu-debugger.cpp
            ui/debugger/debugger.cpp
            ui/debugger/memory-editor.cpp
            ui/debugger/smp-debugger.cpp
        )
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
    ui/file-browser.cpp
    ui/main-window.cpp
    ui/slot-loader.cpp
    ui/advanced-settings.cpp
    ui/audio-settings.cpp
    ui/input-settings.cpp
    ui/video-settings.cpp
    ui/cheat-editor.cpp
    ui/state-manager.cpp
    ui/input.cpp
    ui/utility.cpp
    ui/cartridge.cpp
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

    ## So main() is redefined in this file, but I'm not sure
    ## what the launcher does that the defim binary doesn't
    ## already do.  Meanwhile, I'll just excluse this file
    # launcher/launcher.cpp

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

add_executable(defimulator ${sources})

if(BUILD_LAUNCHER)
    add_executable(launcher
        launcher/launcher.cpp
    )
endif()

if(WIN32)
    target_link_libraries(defimulator
        mingw32
        ${OPENGL_LIBRARIES}
        dsound
        dxguid
        dinput8
        comctl32
    )
else()
    target_link_libraries(defimulator
        # Toolkit libraries
        ${GTK2_LIBRARIES}

        # Graphics Libraries
        ${OPENGL_LIBRARIES}
        ${SDL_LIBRARIES}
        ${X11_LIBRARIES}

        # Audio Libraries
        ${ALSA_LIBRARIES}

        # For -ldl on *nix
        ${CMAKE_DL_LIBS}
    )
endif()

if(BUILD_GAMEBOY)
    target_link_libraries(defim ${CURSES_LIBRARIES})
endif()
