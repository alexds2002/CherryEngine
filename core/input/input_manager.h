#pragma once

/*
 * TODO: Add the functionality to Register/Unregister (with callbacks, maybe std::function?, the class to be captured or NULL, and the actual event to connect to)
 * The InputManager is going to function like an observer. It will have clients connected to events(key pressed, mouse pressed...)
 * and will dispatch each time a key is pressed on the current window.
 */

#include <vector>
#include <utility>
#include <functional>
#include <unordered_map>
#include <Singleton.h>
#include <project_definitions.h>

class GLFWwindow;

class InputManager : public Singleton<InputManager>
{
public:
    InputManager();
    void Init(GLFWwindow* window);
    void PollEvents();

    /* TODO(Alex): add templated version like the thread pool one. Currently supports only void(). */
    /* TODO(Alex): add move semantics optimizations */
    void BindAction(KeyCode key, KeyState state, std::function<void()> callback);
    /* TODO(Alex): add option for dispatch on current key without state */
    void DispatchKeyEvent(KeyCode key, KeyState state);

    Position GetMousePosition();
    double GetMouseX();
    double GetMouseY();

private:
    /*
     * Everything connected to a key event with a key state.
     * W_KEY, KEY_PRESSED, actual callback.
     * Ensures O(1) insertion
     */
    //std::unordered_multimap<KeyCode, std::unordered_multimap<KeyState, std::function<void()>>> m_eventKeyCallbacks;
    std::unordered_map<KeyCode, std::unordered_map<KeyState, std::vector<std::function<void()>>>> m_eventKeyCallbacks;

    Position m_mousePosition;
};

