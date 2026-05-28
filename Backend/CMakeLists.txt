# Versioning & Configuration
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
project(GLEBackend LANGUAGES CXX)

add_library(
    GLEBackend
    src/dummy.cpp
    src/glfw.cpp
)

target_include_directories(
    GLEBackend
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

target_link_libraries(GLEBackend
    PUBLIC
        GLECore
        GLEInterface
)

# External libraries

# Define macro for importing GitHub repos
include(FetchContent)

macro(ImportRepo NAME REPO COMMIT)
    message(
        STATUS 
        "Module: ${NAME} @ ${COMMIT}"
    )

    FetchContent_Declare(
        ${NAME}
        GIT_REPOSITORY ${REPO}
        GIT_TAG        ${COMMIT}      # exact commit from lockfile
        GIT_SHALLOW    TRUE
        UPDATE_DISCONNECTED FALSE
    )

    FetchContent_MakeAvailable(${NAME})
endmacro()

# GLAD
ImportRepo(glad https://github.com/Dav1dde/glad.git 5bf3eda)
add_library(glad STATIC ${glad_SOURCE_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${glad_SOURCE_DIR}/include)
target_link_libraries(GLEBackend PRIVATE glad)

# GLFW
ImportRepo(GLFW https://github.com/glfw/glfw.git 3.4)
target_link_libraries(GLEBackend PRIVATE glfw)

target_include_directories(
    GLEBackend
    PRIVATE

    # Import includes
    "${glad_SOURCE_DIR}/include"
    "${glfw_SOURCE_DIR}/include"
    "${glm_SOURCE_DIR}"
    "${stbimage_SOURCE_DIR}"
)