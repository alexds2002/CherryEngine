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
    m_game = std::make_unique<Game>();
    m_renderer2D = std::make_unique<Renderer2D>();

    if(!m_game->Init())
    {
        Debug_Log(ELogCategory::Error, "Game cound not be initilzed!");
    }
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
    m_game->Update();
    // Orthographic projection matrix
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

    bool renderer2d_initialized =
        m_renderer2D->Init("../core/render/vertex_shader.glsl",
                        "../core/render/fragment_shader.glsl",
                        projection);
    if(!renderer2d_initialized)
    {
        Debug_Log(ELogCategory::Error, EPrintColor::Red, true, "Renderer2D failed to initialize!");
    }

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
        m_renderer2D->drawQuad(glm::vec2(400.0f, 350.0f), glm::vec2(100.0f, 100.0f), rss_manager->GetTexturePtr("berserk.png")); // Quad with texture1

        glfwSwapBuffers(m_window->GetGLFWwindow());
    }
}

void Application::RenderTexture(Position pos, int xSize, int ySize, const std::string& key)
{
}

