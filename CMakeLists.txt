cmake_minimum_required(VERSION 3.28)
project(65emu2 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(sfemu2 src/main.c
        include/opcodes.h)
add_executable(sfemu2dis src/disasm.c
        include/opcodes.h)
