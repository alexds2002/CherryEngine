cmake_minimum_required(VERSION 3.16)
# TODO(Alex): Update to 23
set(CMAKE_CXX_STANDARD 20)
project(CherrY)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

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

target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
