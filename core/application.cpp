#include "application.h"
#include "window.hpp"
#include "render/renderer2D.h"
#include "../game/game.h"

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
    m_rssManager = std::make_unique<ResourceManager>();
    m_renderer2D = std::make_shared<Renderer2D>();

    m_game = std::make_unique<Game>(m_renderer2D);

    // Orthographic projection matrix
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
    const char* vertex_shared_key = "../core/render/vertex_shader.glsl";
    const char* fragment_shared_key = "../core/render/fragment_shader.glsl";

    // Set OpenGL context and loads glad so it must be initialized first
    if(!m_window->Init())
    {
        Debug_Log(ELogCategory::Error, "Window cound not be initilzed!");
        return false;
    }
    if(!m_game->Init())
    {
        Debug_Log(ELogCategory::Error, "Game cound not be initilzed!");
    }
    if(!m_renderer2D->Init(vertex_shared_key, fragment_shared_key, projection))
    {
        Debug_Log(ELogCategory::Error, EPrintColor::Red, true, "Renderer2D failed to initialize!");
    }
    InputManager::GetInstance()->Init(m_window->GetGLFWwindow()); // Init after m_window is initialized!

    m_rssManager->LoadResources();
    m_window->SetVSyncOn();

    // Example uses of the InputManager
    InputManager::GetInstance()->BindToMouseMove([](int x, int y){ std::cout << x << " " << y << std::endl; });
    InputManager::GetInstance()->BindMouseEvent(CHERRY_MOUSE_BUTTON_1, CHERRY_PRESS, [](){ std::cout << "Mouse clicked" << std::endl; });

    return true;
}

// TODO(Alex) move the while loop in the main.cpp file and calculate the deltatime
void Application::Update(double deltaTime)
{
    // Main loop
    while (!glfwWindowShouldClose(m_window->GetGLFWwindow()))
    {
        m_game->Update(m_deltaTime);
        InputManager::GetInstance()->PollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use Renderer
        m_renderer2D->drawQuad(glm::vec2(400.0f, 350.0f), glm::vec2(100.0f, 100.0f), m_rssManager->GetTexturePtr("berserk.png")); // Quad with texture1

        glfwSwapBuffers(m_window->GetGLFWwindow());
    }
}

