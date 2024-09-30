#include "application.h"
#include "window.hpp"
#include "render/renderer2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <input_manager.h>
#include <project_definitions.h>
#include <debug_logger_component.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

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
    // Orthographic projection matrix
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

    // Create Renderer2D instance
    // TODO(Alex): remove absolute paths to the shaders
    Renderer2D renderer("/home/default/education/education/lectures/OpenGL/core/render/vertex_shader.glsl",
                        "/home/default/education/education/lectures/OpenGL/core/render/fragment_shader.glsl",
                        projection);

    // Load multiple textures
    unsigned int texture1 = renderer.loadTextureFromFile("../data/berserk.png");

    // Main loop
    while (!glfwWindowShouldClose(m_window->GetGLFWwindow()))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions.
        InputManager::GetInstance()->PollEvents();

        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use Renderer

        // Draw multiple textured quads with different positions and textures
        renderer.drawQuad(glm::vec2(400.0f, 350.0f), glm::vec2(100.0f, 100.0f), texture1);  // Quad with texture1

        // Swap the screen buffers
        glfwSwapBuffers(m_window->GetGLFWwindow());
    }
}

