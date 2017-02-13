cmake_minimum_required(VERSION 3.0)
project(bsuite)

# Set the emulation profile.  Variables are pretty self-explantory.
set(EMULATION_PROFILE "PERFORMANCE" CACHE STRING "Emulation profile.")
set_property(CACHE EMULATION_PROFILE PROPERTY STRINGS
    ACCURACY COMPATIBILITY PERFORMANCE)

# Debugger is broke.
option(BUILD_DEUBGGER "Not compatible with PERFORMANCE profile." OFF)
option(BUILD_FILTERS "Build SNES filers." ON)
option(BUILD_LAUNCHER "Build bsnes launcher.  Unknown usage.." OFF)

# If no build type is specified, assume the user wants a release build.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "'Debug' or 'Release'" FORCE)
endif()

message(">>>> Using ${EMULATION_PROFILE} emulation profile.")
message(">>>> Build type: ${CMAKE_BUILD_TYPE}")


if(NOT WIN32)
    find_package(PkgConfig)
    find_package(OpenGL)
    pkg_search_module(GTK2 REQUIRED gtk+-2.0)
    pkg_search_module(SDL REQUIRED sdl)
    pkg_search_module(X11 REQUIRED x11)
    pkg_search_module(ALSA REQUIRED alsa)
    pkg_search_module(PULSE REQUIRED libpulse)
    if(BUILD_GAMEBOY)
        pkg_search_module(CURSES REQUIRED ncurses)
    endif()
endif()

subdirs(bsnes)
subdirs(snespurify)

if(BUILD_FILTERS)
    message(">>>> Building filters.")
    subdirs(snesfilter)
endif()
