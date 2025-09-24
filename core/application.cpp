#include "application.h"
#include "window.hpp"
#include "render/renderer2D.h"
#include "../runtime/runtime.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <input_manager.h>
#include <project_definitions.h>
#include <debug_logger_component.h>
#include <release_logger_component.h>
#include <debug_assert_component.h>
#include <resource_manager.h>
#include <memory>
#include <chrono>

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
    Debug_Log(ELogCategory::Core, EPrintColor::LightGreen, "Starting Cherry Engine...");
    m_window = std::make_unique<Window>();
    m_rssManager = std::make_unique<ResourceManager>();
    m_renderer2D = std::make_shared<Renderer2D>();

    m_runtime = std::make_unique<Runtime>(m_renderer2D);

    // Orthographic projection matrix
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
    const char* vertex_shared_key = "../core/render/vertex_shader.glsl";
    const char* fragment_shared_key = "../core/render/fragment_shader.glsl";

    // Set OpenGL context and loads glad so it must be initialized first
    Debug_Log(ELogCategory::Core, EPrintColor::LightGreen, "Initializing Window...");
    if(!m_window->Init())
    {
        Debug_Log(ELogCategory::Error, "Window cound not be initilzed!");
        return false;
    }
    Debug_Log(ELogCategory::Core, EPrintColor::LightGreen, "Initializing Runtime...");
    if(!m_runtime->Init())
    {
        Debug_Log(ELogCategory::Error, "Runtime cound not be initialized!");
    }
    Debug_Log(ELogCategory::Core, EPrintColor::LightGreen, "Initializing Renderer...");
    if(!m_renderer2D->Init(vertex_shared_key, fragment_shared_key, projection))
    {
        Debug_Log(ELogCategory::Error, EPrintColor::Red, true, "Renderer2D failed to initialize!");
    }
    Debug_Log(ELogCategory::Core, EPrintColor::LightGreen, "Initializing InputManager...");
    InputManager::GetInstance()->Init(m_window->GetGLFWwindow()); // Init after m_window is initialized!

    m_rssManager->LoadResources();
    m_window->SetVSyncOff();

    // Example uses of the InputManager
    // InputManager::GetInstance()->BindToMouseMove([](int x, int y){ std::cout << x << " " << y << std::endl; });
    // InputManager::GetInstance()->BindMouseEvent(CHERRY_MOUSE_BUTTON_1, CHERRY_PRESS, [](){ std::cout << "Mouse clicked" << std::endl; });

    return true;
}

// TODO(Alex) move the while loop in the main.cpp file and calculate the deltatime
void Application::Update()
{
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    float timeAccumulator = 0.0f;
    float frameCount = 0.0f;

    // Main loop
    while (!glfwWindowShouldClose(m_window->GetGLFWwindow()))
    {
        // calculate delta time and fps
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> delta = currentTime - lastFrameTime;
            lastFrameTime = currentTime;
            m_deltaTime = delta.count();

            timeAccumulator += m_deltaTime;
            frameCount++;
            m_fps = static_cast<int>(frameCount / timeAccumulator);

            if(timeAccumulator >= 1.0f)
            {
                CHERRY_ASSERT(m_window->GetGLFWwindow() && strcmp(std::to_string(m_fps).c_str(), ""));
                // set window title to the fps every second
                glfwSetWindowTitle(m_window->GetGLFWwindow(), (m_window->GetTitle() + " " + std::to_string(m_fps) + "FPS").c_str());
                // reset frames and timer
                timeAccumulator = 0.f;
                frameCount = 0.f;
            }
        }
        m_runtime->Update(m_deltaTime);
        InputManager::GetInstance()->PollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use Renderer
        m_renderer2D->drawQuad(glm::vec2(400.0f, 350.0f), glm::vec2(100.0f, 100.0f), m_rssManager->GetTexturePtr("berserk.png")); // Quad with texture1
        glfwSwapBuffers(m_window->GetGLFWwindow());
    }
}

