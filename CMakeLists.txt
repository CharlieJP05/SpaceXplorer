cmake_minimum_required(VERSION 3.30)
project(SpaceXplorer C)

#add_custom_target(custom_build
#        COMMAND ${CMAKE_SOURCE_DIR}/build.sh
#        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#        COMMENT "Running custom build script..."
#)

set(CMAKE_C_STANDARD 11)
add_executable(SpaceXplorer main.c
        funcs.c
        structs.c
        funcs.h
        structs.h
)