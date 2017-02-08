cmake_minimum_required(VERSION 3.0)
project(bsnes)

# This toggle does nothing currently.
set(EMULATION_PROFILE "Accuracy" CACHE STRING
    "Options are Speed, Accuracy and Balance")
set_property(CACHE EMULATION_PROFILE PROPERTY STRINGS Accuracy Speed Balance)

find_package(PkgConfig)

# pkg_search_module(SDL REQUIRED sdl)
pkg_search_module(GTK2 REQUIRED gtk+-2.0)

subdirs(snespurify)
