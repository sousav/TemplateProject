# stop if cmake version below 3.0
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# project name
project(ArgParser)

# location of additional cmake modules
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/CMake
)

set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS         "-std=c++11 -W -Wall -Wextra -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SRC_FILES
        ${PROJECT_SOURCE_DIR}/Includes/ArgParser.h
        ${PROJECT_SOURCE_DIR}/Sources/ArgParser.cpp
)

# build executable
add_library(ArgParser ${SRC_FILES})

# location of header files
include_directories(
    ${PROJECT_SOURCE_DIR}/Includes
)
