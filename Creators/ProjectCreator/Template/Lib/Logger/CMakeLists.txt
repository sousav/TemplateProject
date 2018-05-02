# stop if cmake version below 3.0
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# project name
project(Logger)

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
        ${PROJECT_SOURCE_DIR}/Includes/Channel.h
        ${PROJECT_SOURCE_DIR}/Includes/Config.h
        ${PROJECT_SOURCE_DIR}/Includes/DateTime.h
        ${PROJECT_SOURCE_DIR}/Includes/Exception.h
        ${PROJECT_SOURCE_DIR}/Includes/Formatter.h
        ${PROJECT_SOURCE_DIR}/Includes/Log.h
        ${PROJECT_SOURCE_DIR}/Includes/Logger.h
        ${PROJECT_SOURCE_DIR}/Includes/LoggerCpp.h
        ${PROJECT_SOURCE_DIR}/Includes/Manager.h
        ${PROJECT_SOURCE_DIR}/Includes/Output.h
        ${PROJECT_SOURCE_DIR}/Includes/OutputConsole.h
        ${PROJECT_SOURCE_DIR}/Includes/OutputDebug.h
        ${PROJECT_SOURCE_DIR}/Includes/OutputFile.h
        ${PROJECT_SOURCE_DIR}/Includes/Utils.h
        ${PROJECT_SOURCE_DIR}/Includes/shared_ptr.hpp
        ${PROJECT_SOURCE_DIR}/Sources/Config.cpp
        ${PROJECT_SOURCE_DIR}/Sources/DateTime.cpp
        ${PROJECT_SOURCE_DIR}/Sources/Log.cpp
        ${PROJECT_SOURCE_DIR}/Sources/Logger.cpp
        ${PROJECT_SOURCE_DIR}/Sources/Manager.cpp
        ${PROJECT_SOURCE_DIR}/Sources/OutputConsole.cpp
        ${PROJECT_SOURCE_DIR}/Sources/OutputDebug.cpp
        ${PROJECT_SOURCE_DIR}/Sources/OutputFile.cpp
)

# build executable
add_library(Logger ${SRC_FILES})

# location of header files
include_directories(
    ${PROJECT_SOURCE_DIR}/Includes
)
