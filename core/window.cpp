#include "window.hpp"

#include <debug_assert_component.h>
#include <debug_logger_component.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

/*
 * Handles window resize event.
 */
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window()
{
}

Window::~Window()
{
}

bool Window::Init(const std::string& windowName, int width, int height)
{
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

    m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.windowName.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, &m_data);

    // Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error.
    // Needs to be called for each OpenGL Context(unless i want windows to share data)
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        Debug_Log("Failed to initialize glad");
        return -1;
    }
    // Successfully loaded OpenGL
    Debug_Log("Loaded OpenGL ", GLAD_VERSION_MAJOR(version), ".", GLAD_VERSION_MINOR(version));

    glViewport(0, 0, m_data.width, m_data.height);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    return true; // success
}

bool Window::DeInit()
{
    return true; // successful deinitialization
}

/* Returns the actual ptr to GLFWwindow */
GLFWwindow* Window::GetGLFWwindow()
{
    return m_window;
}

void Window::SetVSyncOn()
{
    m_data.VSync = true;
    glfwSwapInterval(1);
}

void Window::SetVSyncOff()
{
    m_data.VSync = false;
    glfwSwapInterval(0);
}
