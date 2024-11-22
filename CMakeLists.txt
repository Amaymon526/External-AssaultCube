cmake_minimum_required(VERSION 3.29)
project(External_AssaultCube)

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--subsystem,console")


include_directories(.)

add_executable(External_AssaultCube
        src/main.cpp
        src/offsets/Offsets.h
        src/memory/memory.cpp
)
