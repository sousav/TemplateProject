cmake_minimum_required(VERSION 3.9)
set(NAME {{project_name}})
project(${NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


## Setup Logger library
if (NOT TARGET Logger)
    add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/Logger)
    include_directories(${PROJECT_SOURCE_DIR}/Lib/Logger/Includes/)
endif()

## Setup Argument parsing library
if (NOT TARGET ArgParser)
    add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/ArgParser)
    include_directories(${PROJECT_SOURCE_DIR}/Lib/ArgParser/Includes/)
endif()

add_library(${NAME} SHARED "")

## Setup the source files
target_sources(${NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/Includes/CppLibrary.h
    ${PROJECT_SOURCE_DIR}/Sources/CppLibrary.cpp
)


## Setup default include path
include_directories(
        ${PROJECT_SOURCE_DIR}/Includes/
)

## Setup link path
link_directories(
        ${PROJECT_BINARY_DIR}/Lib/Logger/
)


## Setup used library
target_link_libraries(${NAME}
        Logger
        ArgParser
)
