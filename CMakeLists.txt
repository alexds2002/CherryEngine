cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(CherrY)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

# Build types are
# Debug
# Release
message("-- CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
if (NOT CMAKE_BUILD_TYPE STREQUAL "")
    string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
    add_compile_definitions("${CMAKE_BUILD_TYPE}_MODE")
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp
                                            src/*.h
                                            src/*.hpp)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/project_definitions)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/components)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
