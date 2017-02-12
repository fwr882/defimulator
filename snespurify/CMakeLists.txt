project(snespurify CXX)
enable_language(C)

include_directories("${snespurify_SOURCE_DIR}")
include_directories("${bsnes_SOURCE_DIR}")

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPHOENIX_WINDOWS")
else()
    include_directories("${GTK2_INCLUDE_DIRS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPHOENIX_GTK")
endif()

add_executable(snespurify
    snespurify.cpp
    phoenix/phoenix.cpp
)

if(WIN32)
    target_link_libraries(snespurify
        mingw32
        comctl32
    )
else()
    target_link_libraries(snespurify ${GTK2_LIBRARIES})
endif()
