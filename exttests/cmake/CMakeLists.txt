project(libSDL2pp)
cmake_minimum_required(VERSION 2.8)

find_package(SDL2PP REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(cmake-ext-test ../../examples/sprites.cc)
target_link_libraries(cmake-ext-test SDL2pp::SDL2pp)
