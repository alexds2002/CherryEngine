cmake_minimum_required(VERSION 3.16)
# TODO(Alex): Update to 23
set(CMAKE_CXX_STANDARD 20)
project(CherrY)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(libs/glfw)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

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

include_directories(${OPENGL_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/project_definitions)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/components)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/algorithms)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include)

# alternatively where to look for lib files
target_link_directories(${PROJECT_NAME} PRIVATE libs/glfw/src)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
