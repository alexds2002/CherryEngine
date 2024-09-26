#include "window.hpp"

#include <debug_assert_component.h>
#include <debug_logger_component.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

Window::Window()
{
}

Window::~Window()
{
}

bool Window::Init(const std::string& windowName, int width, int height)
{
    //TODO(Alex): add glfw init hints
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    m_data.windowName = windowName;
    m_data.width = width;
    m_data.height = height;
    m_data.VSync = false;
    if(!s_GLFWInitialized)
    {
        int success = glfwInit();
        CHERRY_ASSERT(success, "GLFW was not initialized!");

        s_GLFWInitialized = true;
    }
    // Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error.
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        Debug_Log("Failed to initialize OpenGL context");
        return -1;
    }
    // Successfully loaded OpenGL
    Debug_Log("Loaded OpenGL ", GLAD_VERSION_MAJOR(version), ".", GLAD_VERSION_MINOR(version));

    m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.windowName.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, &m_data);
    return true; // success
}

bool Window::DeInit()
{
    return true; // successful deinitialization
}

GLFWwindow* Window::GetGLFWwindow()
{
    return m_window;
}

