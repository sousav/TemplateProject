cmake_minimum_required(VERSION 3.9)
project(TemplateProject)

set(CMAKE_CXX_STANDARD 17)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

find_package(Boost REQUIRED COMPONENTS system filesystem)

add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/Logger)
add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/ArgParser)

add_executable(TemplateProject
        ${PROJECT_SOURCE_DIR}/Sources/main.cpp

        ${PROJECT_SOURCE_DIR}/Includes/IMain.h
        ${PROJECT_SOURCE_DIR}/Includes/AMain.h
        ${PROJECT_SOURCE_DIR}/Sources/AMain.cpp

        ${PROJECT_SOURCE_DIR}/Includes/IClass.h
        ${PROJECT_SOURCE_DIR}/Includes/AClass.h
        ${PROJECT_SOURCE_DIR}/Sources/AClass.cpp

        ${PROJECT_SOURCE_DIR}/Includes/MainClass.h
        ${PROJECT_SOURCE_DIR}/Sources/MainClass.cpp
)

link_directories(
        ${PROJECT_BINARY_DIR}/Lib/Logger/
)

target_link_libraries(TemplateProject
        Logger
        ArgParser
        boost_system
        boost_filesystem
)

include_directories(
        ${PROJECT_SOURCE_DIR}/Includes/
        ${PROJECT_SOURCE_DIR}/Lib/Logger/Includes/
)
