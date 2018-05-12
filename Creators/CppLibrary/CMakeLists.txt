cmake_minimum_required(VERSION 3.9)

set(NAME CppLibrary)
project(${NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Boost REQUIRED COMPONENTS system filesystem)

## Setup Embeded file library
if (NOT TARGET embed-resource)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Lib/embed-resource/)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Lib/embed-resource/)
endif()

## Setup Logger library
if (NOT TARGET Logger)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Lib/Logger)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Lib/Logger/Includes/)
endif()

## Setup Argument parsing library
if (NOT TARGET ArgParser)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Lib/ArgParser)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Lib/ArgParser/Includes/)
endif()

## Setup the embeded project templates files
embed_resources(Ressources Template.gz)

## Create library
add_library(${NAME} SHARED "")

## Setup common creator sources
include(${CMAKE_CURRENT_SOURCE_DIR}/../Common/Common.cmake)

## Setup the source files
target_sources(${NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/Includes/ProjectCreator.h
    ${PROJECT_SOURCE_DIR}/Sources/ProjectCreator.cpp
    ${Ressources}
)

## Setup default include path
include_directories(
        ${PROJECT_SOURCE_DIR}/Includes/
)

## Setup default link path
link_directories(
        ${PROJECT_BINARY_DIR}/Lib/Logger/
)

## Setup used library
target_link_libraries(${NAME}
        Logger
        ArgParser
        boost_system
        boost_filesystem
)


## build the embeded file before building project
add_custom_target(${NAME}CompressTemplate COMMAND rm -f ${PROJECT_SOURCE_DIR}/Template.gz && tar -cf ${PROJECT_SOURCE_DIR}/Template.gz -C ${PROJECT_SOURCE_DIR}/Template ./ COMMENT "Compressing ${NAME} template")

add_dependencies(${NAME} ${NAME}CompressTemplate)

## Copy the generated library after building project
IF(DEFINED MOVE_CREATOR_LIBRARY)
    add_custom_command(TARGET ${NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${NAME}> ${MOVE_CREATOR_LIBRARY} COMMENT "Copying ${NAME} library")
ENDIF()

add_custom_target(${NAME}BuildTemplate rm -f ${CMAKE_BINARY_DIR}/Creators/CppLibrary/Template.gz.c && make CppLibrary)

install(TARGETS ${NAME} DESTINATION bin/TemplateProjectCreator/Creators)
