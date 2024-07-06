cmake_minimum_required(VERSION 3.12)
project(CherrY)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(GLFW_INCLUDE_PATH "D:/OpenGL/include/glfw32/include")
include_directories(${GLFW_INCLUDE_PATH})
include_directories(${OPENGL_INCLUDE_DIRS})

add_subdirectory(glfw)

option(GLFW-CMAKE-STARTER-USE-GLFW-GLAD "Use GLAD from GLFW" ON)
if( GLFW-CMAKE-STARTER-USE-GLFW-GLAD )
    include_directories("${GLFW_SOURCE_DIR}/deps")
    set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h")
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${GLAD_GL})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
