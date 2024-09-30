#include "application.h"
#include "window.hpp"

#include <debug_logger_component.h>
#include <project_definitions.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <input_manager.h>
#include <std_image.h>

Application::Application()
{
}

Application::~Application()
{
    // Terminate GLFW, clearing any resources allocated by GLFW.
    // TODO: if you have multiple application instances you might not want to do that?
    glfwTerminate();
}

bool Application::Init()
{
    Debug_Log(ELogCategory::Default, EPrintColor::Magenta, "Loading Cherry Engine...");
    m_window = std::make_unique<Window>();
    if(!m_window->Init())
    {
        Debug_Log(ELogCategory::Error, "Window cound not be initilzed!");
        return false;
    }

    InputManager::GetInstance()->Init(m_window->GetGLFWwindow()); // Init after m_window is initialized!

    m_window->SetVSyncOn(); // vsync on by default
    return true; // success
}

void Application::Update(double deltaTime)
{
    // Main loop
    while (!glfwWindowShouldClose(m_window->GetGLFWwindow()))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions.
        InputManager::GetInstance()->PollEvents();

        // Use Renderer

        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the screen buffers
        glfwSwapBuffers(m_window->GetGLFWwindow());
    }
}

