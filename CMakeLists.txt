cmake_minimum_required(VERSION 3.9)
set(NAME TemplateProject)
project(${NAME})

set(CMAKE_CXX_STANDARD 17)
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


## Find required library
find_package(Boost REQUIRED COMPONENTS system filesystem regex)


## Setup Logger library
if (NOT TARGET Logger)
    add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/Logger)
endif()
include_directories(${PROJECT_SOURCE_DIR}/Lib/Logger/Includes/)

## Setup Argument parsing library
add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/ArgParser)
include_directories(${PROJECT_SOURCE_DIR}/Lib/ArgParser/Includes/)


## Setup the source files
set(Sources
    ${PROJECT_SOURCE_DIR}/Sources/main.cpp

    ${PROJECT_SOURCE_DIR}/Includes/IMain.h
    ${PROJECT_SOURCE_DIR}/Includes/AMain.h
    ${PROJECT_SOURCE_DIR}/Sources/AMain.cpp

    ${PROJECT_SOURCE_DIR}/Includes/IClass.h
    ${PROJECT_SOURCE_DIR}/Includes/AClass.h
    ${PROJECT_SOURCE_DIR}/Sources/AClass.cpp

    ${PROJECT_SOURCE_DIR}/Includes/MainClass.h
    ${PROJECT_SOURCE_DIR}/Sources/MainClass.cpp

    ${PROJECT_SOURCE_DIR}/Includes/CreatorLoader.h
    ${PROJECT_SOURCE_DIR}/Sources/CreatorLoader.cpp
)

## Setup default include path
include_directories(
        ${PROJECT_SOURCE_DIR}/Includes/
)

## Setup default link path
link_directories(
        ${PROJECT_BINARY_DIR}/Lib/Logger/
)

## Create executables
add_executable(${NAME} ${Sources})

## Setup common creator sources
include(${CMAKE_SOURCE_DIR}/Creators/Common/Common.cmake)

## Setup used library
target_link_libraries(${NAME}
        Logger
        ArgParser
        boost_regex
        boost_system
        boost_filesystem
)

SET(MOVE_CREATOR_LIBRARY ${PROJECT_BINARY_DIR}/Creators CACHE STRING "Need to mv every generated creator library")
add_subdirectory(${PROJECT_SOURCE_DIR}/Creators/)
