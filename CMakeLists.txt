cmake_minimum_required(VERSION 3.10)
project(psx_emu)

set(CMAKE_CXX_STANDARD 14)

add_executable(psx_emu src/driver.cpp src/cpu.cpp src/cpu.h src/bios.cpp src/bios.h src/memory_bus.cpp src/memory_bus.h src/instruction.cpp src/instruction.h src/register_shorthands.h)