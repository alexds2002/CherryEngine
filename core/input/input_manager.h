#pragma once

/*
 * TODO: Add the functionality to Register/Unregister (with callbacks, maybe std::function?, the class to be captured or NULL, and the actual event to connect to)
 */

#include <vector>

class GLFWwindow;
class Subscribers;
struct Position;

class InputManager
{
public:
    void Init(GLFWwindow* window);

    void PollEvents();

    // Keyboard functions
    bool IsKeyPressed(int key);

    // Mouse functions
    bool IsMouseButtonPressed(int button);
    double GetMouseX();
    double GetMouseY();
    Position GetMousePosition();
private:
    std::vector<Subscribers> m_subscribers;
};

