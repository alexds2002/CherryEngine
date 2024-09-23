#include "Application.h"
#include <debug_logger_component.h>
#include <debug_mode_definitions.h>
#include <debug_assert_component.h>
#include <release_logger_component.h>
#include <benchmark_component.h>
#include <heap_memory_track_component.h>
#include <stack_memory_track_component.h>
#include <project_definitions.h>
#include <string_algorithms.h>
#include <array_algorithms.h>
#include <linked_list_algorithms.h>

#include <GLFW/glfw3.h>

bool Application::Init()
{
    Debug_Log(ELogCategory::Default, EPrintColor::Magenta, "Starting Cherry Engine...");
    GLFWwindow* window;

    /* Init GLFW */
    if( !glfwInit() )
       exit( EXIT_FAILURE );

    window = glfwCreateWindow( 400, 400, "Boing (classic Amiga demo)", NULL, NULL );
    if (!window)
    {
        glfwTerminate();
        exit( EXIT_FAILURE );
    }
    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    exit( EXIT_SUCCESS );

    return true; /* success */
}

void Application::Update(double deltaTime)
{
    while(true)
    {
    }
}
