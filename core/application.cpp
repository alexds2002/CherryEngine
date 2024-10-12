#include "application.h"
#include "window.hpp"
#include "render/renderer2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <input_manager.h>
#include <project_definitions.h>
#include <debug_logger_component.h>
#include <resource_manager.h>
#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

Application::Application()
{
}

Application::~Application()
{
    // Terminate GLFW, clearing any resources allocated by GLFW.
    // WARNING: if you have multiple application instances you might not want to do that?
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

    m_window->SetVSyncOn();
    return true;
}

void Application::Update(double deltaTime)
{
    // Orthographic projection matrix
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

    // Create Renderer2D instance
    // the files user relative to the executable paths
    Renderer2D renderer("../core/render/vertex_shader.glsl",
                        "../core/render/fragment_shader.glsl",
                        projection);

    std::unique_ptr<ResourceManager> rss_manager = std::make_unique<ResourceManager>();
    InputManager::GetInstance()->BindToMouseMove([](int x, int y){ std::cout << x << " " << y << std::endl;});
    InputManager::GetInstance()->BindMouseEvent(CHERRY_MOUSE_BUTTON_1, CHERRY_PRESS, [](){ std::cout << "Mouse clicked" << std::endl;});

    // Main loop
    while (!glfwWindowShouldClose(m_window->GetGLFWwindow()))
    {
        InputManager::GetInstance()->PollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use Renderer
        renderer.drawQuad(glm::vec2(400.0f, 350.0f), glm::vec2(100.0f, 100.0f), rss_manager->GetTexturePtr("berserk.png")); // Quad with texture1

        glfwSwapBuffers(m_window->GetGLFWwindow());
    }
}

