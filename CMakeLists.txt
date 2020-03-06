cmake_minimum_required(VERSION 3.15)
project(player)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17 -O2")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -O0")

include_directories(src test)

add_library(lib_playlist STATIC src/player.cc src/playlist.cc src/product.cc
        src/playable.cc src/file.cc src/playing_mode.cc src/playing_mode.h
        src/player_exception.cc)

add_executable(sample test/sample.cpp)
target_link_libraries(sample lib_playlist)
