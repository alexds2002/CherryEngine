cmake_minimum_required(VERSION 3.16)
project(CherrY)

# Build types are
# Debug
# Release
message("-- CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
if (NOT CMAKE_BUILD_TYPE STREQUAL "")
    string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
    add_compile_definitions("${CMAKE_BUILD_TYPE}_MODE")
endif()

# TODO(Alex): Update to 23
set(CMAKE_CXX_STANDARD 20)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (CMAKE_BUILD_TYPE STREQUAL "DEBUG_MODE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -O0")
elseif(CMAKE_BUILD_TYPE STREQUAL "RELEASE_MODE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

# Add GLM as a subdirectory
add_subdirectory(libs/glm)
# Add the GLFW submodule
add_subdirectory(libs/glfw)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS core/*.cpp
                                                 core/*.hpp
                                                 core/*.h)

file(GLOB_RECURSE EDITOR_SOURCES CONFIGURE_DEPENDS editor/*.cpp
                                                   editor/*.hpp
                                                   editor/*.h)

# Tell cmake to build the sandbox
if (BUILD_SANDBOX)
    message("-- Sandbox build")
    file(GLOB_RECURSE SANDBOX_SOURCES CONFIGURE_DEPENDS sandbox/*.cpp
                                                        sandbox/*.hpp
                                                        sandbox/*.h)
endif()

# Add all sources
# Manually add the glad library
add_executable(${PROJECT_NAME}
               ${CORE_SOURCES}
               ${EDITOR_SOURCES}
               ${SANDBOX_SOURCES}
               libs/glad/generated/src/gl.c)

# Tell CMake to include GLM headers
include_directories(libs/glm)
# Include the GLAD headers
include_directories(${PROJECT_NAME} PRIVATE libs/glad/generated/include)
include_directories(${OPENGL_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/project_definitions)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/thread_pool)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/components)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/input)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include)

# alternatively where to look for lib files
target_link_directories(${PROJECT_NAME} PRIVATE libs/glfw/src)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw glm)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
