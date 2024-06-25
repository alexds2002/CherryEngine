#include <iostream>
#include <GLFW/glfw3.h>

int main()
{
    std::cout << "Cherry Engine Start :D" << std::endl;
    GLFWwindow* window;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    while(!glfwWindowShouldClose(window))
    {
    }
    return 0;
}
