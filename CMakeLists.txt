cmake_minimum_required(VERSION 3.9)
set(NAME TemplateProject)
project(${NAME})

set(CMAKE_CXX_STANDARD 17)
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


## Find required library
find_package(Boost REQUIRED COMPONENTS system filesystem regex)

## Setup Embeded file library
if (NOT TARGET embed-resource)
    add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/embed-resource/)
    include_directories(${PROJECT_SOURCE_DIR}/Lib/embed-resource/)
endif()

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

    ${PROJECT_SOURCE_DIR}/Includes/ExecutablePath.h
    ${PROJECT_SOURCE_DIR}/Sources/ExecutablePath.cpp
)

## Setup common creator Include
include_directories(${CMAKE_SOURCE_DIR}/Creators/Common/Includes)

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


## install rules
macro(install_symlink filepath sympath)
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_INSTALL_PREFIX}/bin/${filepath} ${CMAKE_INSTALL_PREFIX}/bin/${sympath})")
    install(CODE "message(\"-- Created symlink: ${CMAKE_INSTALL_PREFIX}/bin/${sympath} -> ${CMAKE_INSTALL_PREFIX}/bin/${filepath}\")")
endmacro(install_symlink)

install(TARGETS ${NAME} DESTINATION bin/${NAME}Creator)
install(DIRECTORY DESTINATION bin/${NAME}Creator/Creators)
install_symlink(${NAME}Creator/${NAME} ${NAME})
