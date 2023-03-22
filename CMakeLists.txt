cmake_minimum_required(VERSION 3.10.2)

project(ttk)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(main
	src/display/Console.cpp
	src/display/TileRenderer.cpp
	src/display/Window.cpp
	src/main.cpp)
target_link_libraries(main ${SDL2_LIBRARIES})

set(EnTT_DIR libs/entt)
target_include_directories(main PRIVATE ${EnTT_DIR}/src)

#find_package(EnTT REQUIRED)
#target_link_libraries(main EnTT::EnTT)
