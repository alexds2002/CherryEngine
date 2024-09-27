#include "input_manager.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <project_definitions.h>

void InputManager::Init(GLFWwindow* window)
{
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, MousePositionCallback);
}
void InputManager::PollEvents()
{
}

// Keyboard functions
bool InputManager::IsKeyPressed(int key)
{
}

// Mouse functions
bool InputManager::IsMouseButtonPressed(int button)
{
}
double InputManager::GetMouseX()
{
}
double InputManager::GetMouseY()
{
}
Position InputManager::GetMousePosition()
{
}
