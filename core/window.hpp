#pragma once

/*
 * This class is an abstraction of the GLFWwindow.
 * It will hold window data and potention for cross platform implementations.
 */

#include <string>

class GLFWwindow;

class Window
{
public:
    Window();
    ~Window();
    bool Init(const std::string& windowName = "Cherry Engine", int width = 1080, int height = 720);
    bool DeInit();
    void SetVSyncOn();
    void SetVSyncOff();
    GLFWwindow* GetGLFWwindow();

private:
    // Avoid multiple glfw initializations
    inline static bool s_GLFWInitialized = false;
    struct WindowData
    {
        std::string windowName;
        int width;
        int height;
        bool VSync;
    };
    GLFWwindow* m_window;
    WindowData m_data;
};

