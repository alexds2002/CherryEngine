# game is linked as library
cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(game_lib ${GAME_SOURCES})

target_include_directories(game_lib PUBLIC ${CMAKE_SOURCE_DIR}/core/project_definitions)
target_include_directories(game_lib PUBLIC ${CMAKE_SOURCE_DIR}/core/thread_pool)
target_include_directories(game_lib PUBLIC ${CMAKE_SOURCE_DIR}/core/components)
target_include_directories(game_lib PUBLIC ${CMAKE_SOURCE_DIR}/core/input)
target_include_directories(game_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
