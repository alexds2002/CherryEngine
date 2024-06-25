cmake_minimum_required(VERSION 3.10)
project(CherrY)

set(CMAKE_CXX_STANDARD 17)

set(STATIC_LIB_PATH "D:/OpenGL/include/glfw32/lib-vc2015")
set(INCLUDE_PATH "D:/OpenGL/include/glfw32/include")

include_directories(${INCLUDE_PATH})

add_executable(${PROJECT_NAME} src/main.cpp)

# Link the static library
target_link_libraries(${PROJECT_NAME} "${STATIC_LIB_PATH}/glfw3.lib")
