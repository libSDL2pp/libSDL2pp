cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(Test)

find_package(SDL2pp REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(cmake-ext-test ../../examples/sprites.cc)
target_link_libraries(cmake-ext-test SDL2pp::SDL2pp)
