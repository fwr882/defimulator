project(snespurify CXX)
enable_language(C)

include_directories("${snespurify_SOURCE_DIR}")
include_directories("${GTK2_INCLUDE_DIRS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPHOENIX_GTK")

add_executable(snespurify
    snespurify.cpp
    phoenix/phoenix.cpp
)

target_link_libraries(snespurify ${GTK2_LIBRARIES})
