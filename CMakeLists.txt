cmake_minimum_required(VERSION 3.30)
project(SpaceXplorer C)

set(CMAKE_C_STANDARD 11)

add_executable(SpaceXplorer main.c
        structs.h
        funcs.c
        funcs.h
        structs.c)
