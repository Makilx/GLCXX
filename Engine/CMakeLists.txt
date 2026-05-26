# Versioning & Configuration
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
project(GLEngine LANGUAGES CXX)

add_library(
    GLEngine
    src/dummy.cpp
    src/service/runService.cpp
    src/service/renderService.cpp
    src/instance/instance.cpp
)

target_include_directories(
    GLEngine
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Linking
if(NOT TARGET GLECore)
    add_subdirectory(
        ../Core 
        ${CMAKE_BINARY_DIR}/Core
    )
endif()

if(NOT TARGET GLEInterface)
    add_subdirectory(
        ../Interface 
        ${CMAKE_BINARY_DIR}/Interface
    )
endif()

target_link_libraries(GLEngine
    PUBLIC
        GLECore
        GLEInterface
)