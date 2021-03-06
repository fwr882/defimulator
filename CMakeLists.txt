cmake_minimum_required(VERSION 3.0)
project(defimulator)

# Set the emulation profile.  Variables are pretty self-explantory.
set(EMULATION_PROFILE "PERFORMANCE" CACHE STRING "Emulation profile.")
set_property(CACHE EMULATION_PROFILE PROPERTY STRINGS
    ACCURACY COMPATIBILITY PERFORMANCE)

if(APPLE)
    message(">>>> Detected Apple")
elseif(UNIX)
    message(">>>> Detected UNIX")
elseif(UNIX AND NOT APPLE)
    message(">>>> Detected Linux")
elseif(WIN32)
    message(">>>> Detected Windows")
else()
    message(">>>> Unknown Platform")
endif()

# Debugger is broke with PERFORMANCE profile.
option(BUILD_DEBUGGER "Not compatible with PERFORMANCE or WIN32." OFF)
option(BUILD_FILTERS "Build SNES filers." OFF)
option(BUILD_PURIFY "Build SNES ROM purifying tool." OFF)
option(BUILD_LAUNCHER "Build defimulator launcher.  Unknown usage.." OFF)

# If no build type is specified, assume the user wants a release build.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "'Debug' or 'Release'" FORCE)
endif()

message(">>>> Using ${EMULATION_PROFILE} emulation profile.")
message(">>>> Build type: ${CMAKE_BUILD_TYPE}")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(">>>> Setting debug flags; watch stderr for output.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEFIMULATOR_DEBUG")
endif()

find_package(OpenGL)

if(NOT WIN32)
    find_package(PkgConfig)
    pkg_search_module(GTK2 REQUIRED gtk+-2.0)
    pkg_search_module(SDL REQUIRED sdl)
    pkg_search_module(X11 REQUIRED x11)
    pkg_search_module(PULSE REQUIRED libpulse)

    if(LINUX)
        pkg_search_module(ALSA REQUIRED alsa)
    endif()

    if(BUILD_GAMEBOY)
        pkg_search_module(CURSES REQUIRED ncurses)
    endif()
endif()

subdirs(defimulator)

if(BUILD_PURIFY)
    message(">>>> Building purifier.")
    subdirs(snespurify)
endif()

if(BUILD_FILTERS)
    message(">>>> Building filters.")
    subdirs(snesfilter)
endif()
