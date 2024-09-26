#pragma once

#include <string>

class GLFWwindow;

class Window
{
public:
    Window();
    ~Window();
    bool Init(const std::string& windowName = "Cherry Engine", int width = 1080, int height = 720);
    bool DeInit();
    GLFWwindow* GetGLFWwindow();

private:
    // Avoid multiple window initializations
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

