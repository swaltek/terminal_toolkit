cmake_minimum_required(VERSION 3.10.2)

project(console_toolkit)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(main_test test/main.cpp lib/Console.cpp lib/TileRenderer.cpp lib/Window.cpp)
target_link_libraries(main_test ${SDL2_LIBRARIES})
