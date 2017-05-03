cmake_minimum_required(VERSION 3.0)
project(gtkmm_tests CXX)

find_package(PkgConfig)
pkg_search_module(GTKMM3 REQUIRED gtkmm-3.0)

include_directories("${GTKMM3_INCLUDE_DIRS}")
include_directories("${gtkmm_tests_SOURCE_DIR}/../..")
include_directories("${gtkmm_tests_SOURCE_DIR}/..")

add_executable(gtkmm_test
    main.cpp
    ../advanced-settings.cpp
    ../configuration.cpp
    ../main-window.cpp
    ../menubar.cpp
    ../viewport.cpp)

target_link_libraries(gtkmm_test ${GTKMM3_LIBRARIES})
