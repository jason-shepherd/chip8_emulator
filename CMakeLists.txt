cmake_minimum_required(VERSION 3.7)
project(Chip8_Emulator C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(Chip8_Emulator 
  src/main.c 
  src/chip8 
  src/display.c 
  src/instructions.c
  src/clock.c
  src/input.c
  )

target_link_libraries(Chip8_Emulator ${SDL2_LIBRARIES})
