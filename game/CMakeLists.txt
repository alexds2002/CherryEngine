# game is linked as library
cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )

add_library(game_lib ${GAME_SOURCES})

# set inlcude directories for easy header access
set(GAME_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/core/project_definitions
    ${CMAKE_SOURCE_DIR}/core/thread_pool
    ${CMAKE_SOURCE_DIR}/core/components
    ${CMAKE_SOURCE_DIR}/core/input
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libs/glm
    ${CMAKE_SOURCE_DIR}/libs/glad/generated/include
    ${OPENGL_INCLUDE_DIRS})

target_include_directories(game_lib PUBLIC ${GAME_INCLUDE_DIRECTORIES})
