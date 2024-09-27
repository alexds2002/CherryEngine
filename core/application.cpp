#include "application.h"
#include "window.hpp"

#include <debug_logger_component.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

Application::Application()
{
}

Application::~Application()
{
    // Terminate GLFW, clearing any resources allocated by GLFW.
    // TODO: if you have multiple application instances you might not want to do that(do i want that?)
    glfwTerminate();
}

bool Application::Init()
{
    Debug_Log(ELogCategory::Default, EPrintColor::Magenta, "Starting Cherry Engine...");
    m_window = std::make_unique<Window>();
    if(!m_window->Init())
    {
        Debug_Log(ELogCategory::Error, "Window cound not be initilzed!");
        return false;
    }

    m_window->SetVSyncOn(); // vsync on by default
    return true; // success
}

void Application::Update(double deltaTime)
{
    // Main loop
    while (!glfwWindowShouldClose(m_window->GetGLFWwindow()))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Renderer

        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the screen buffers
        glfwSwapBuffers(m_window->GetGLFWwindow());
    }
}

//TODO(Alex): Implement eventkey system

// Set the required callback functions
// glfwSetKeyCallback(window, key_callback);
/* Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}*/
