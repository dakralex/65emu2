cmake_minimum_required(VERSION 3.28)
project(65emu2 C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(src)
include_directories(include)

add_executable(sfemu2 src/main.c)
add_executable(sfemu2-disasm src/disasm.c)
