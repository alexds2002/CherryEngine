cmake_minimum_required(VERSION 3.10)
project(CherrY)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_PATH "D:/OpenGL/include/glfw32/include")
include_directories(${INCLUDE_PATH})
include_directories(${OPENGL_INCLUDE_DIRS})

add_subdirectory(glfw)

option(GLFW-CMAKE-STARTER-USE-GLFW-GLAD "Use GLAD from GLFW" ON)
if( GLFW-CMAKE-STARTER-USE-GLFW-GLAD )
    include_directories("${GLFW_SOURCE_DIR}/deps")
    set( GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" )
endif()

add_executable(${PROJECT_NAME} WIN32 src/main.cpp ${GLAD_GL})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

