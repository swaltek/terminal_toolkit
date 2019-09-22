cmake_minimum_required(VERSION 3.10.2)

project(console_toolkit)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(main_test
	lib/Console.cpp
	lib/RootConsole.cpp
	lib/TileRenderer.cpp
	lib/Window.cpp
	test/main.cpp)
target_link_libraries(main_test ${SDL2_LIBRARIES})
