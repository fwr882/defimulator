cmake_minimum_required(VERSION 3.0)
project(bsuite)

# This toggle does nothing currently.

#set(EMULATION_PROFILE "ACCURACY")
set(EMULATION_PROFILE "ACCURACY" CACHE STRING "Emulation profile.")
set_property(CACHE EMULATION_PROFILE PROPERTY STRINGS
    ACCURACY COMPATIBILITY PERFORMANCE)

message("Using ${EMULATION_PROFILE} emulation profile.")

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type.")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    Release Debug)

find_package(PkgConfig)
find_package(OpenGL)

pkg_search_module(SDL REQUIRED sdl)
pkg_search_module(GTK2 REQUIRED gtk+-2.0)
pkg_search_module(X11 REQUIRED x11)
pkg_search_module(XEXT REQUIRED xext)
pkg_search_module(XV REQUIRED xv)
pkg_search_module(AO REQUIRED ao)

subdirs(bsnes)
subdirs(snespurify)
