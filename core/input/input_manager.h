#pragma once

/*
 * The InputManager is going to function like an observer. It will have clients connected to events(key pressed, mouse pressed...)
 * and will dispatch each time a key is pressed on the current window.
 *
 * TODO(Alex): Add the functionality to Unregister
 * TODO(Alex): add templated version like the thread pool one. Currently supports only void().
 * TODO(Alex): add move semantics optimizations.
 * TODO(Alex): add option for dispatch on current key without state
 */

#include <vector>
#include <functional>
#include <unordered_map>

#include <Singleton.h>
#include <project_definitions.h>

class GLFWwindow;

/**
 * @file input_manager.h
 * @brief A class for managing input events from the user.
 *
 * The `InputManager` class is responsible for handling keyboard and mouse input
 * events in a GLFW-based application. It allows binding actions to specific key
 * events and dispatching those actions when the corresponding events occur.
 *
 * It implements the Singleton design pattern to ensure a single instance of
 * the input manager exists throughout the application.
 *
 * Usage Example:
 * @code
 * InputManager::GetInstance()->Init(window);
 * InputManager::GetInstance()->BindAction(KeyCode::W, KeyState::KEY_PRESSED, []() {
 *     // Action to perform when 'W' is pressed
 * });
 * @endcode
 */
class InputManager : public Singleton<InputManager>
{
public:
    /**
     * @brief Constructs an `InputManager` default instance.
     */
    InputManager() = default;

    /**
     * @brief Initializes the input manager with a GLFW window.
     *
     * This method must be called before polling events.
     *
     * @param window A pointer to the GLFW window to be used for input events.
     */
    void Init(GLFWwindow* window);

    /**
     * @brief Polls for input events from the GLFW window.
     *
     * This method should be called each frame to process input events.
     */
    void PollEvents();

    /**
     * @brief Binds a callback function to a specific key event and state.
     *
     * This method allows users to specify a callback function that will be
     * called when the specified key is pressed or released.
     *
     * @param key The key code for the key to bind the action to.
     * @param state The key state (e.g., pressed or released) to bind the action to.
     * @param callback The function to call when the key event occurs.
     *
     * @note Currently, only `void()` callback functions are supported.
     *       Future versions may support templated callback types.
     */
    void BindAction(KeyCode key, KeyState state, std::function<void()> callback);

    /**
     * @brief Dispatches a key event.
     *
     * This method is called to handle a key event, triggering the associated
     * callback functions for the specified key and state.
     *
     * @param key The key code for the key event.
     * @param state The key state (e.g., pressed or released) for the event.
     *
     * @note Future versions may include options for dispatching events based
     *       on the current key.
     */
    void DispatchKeyEvent(KeyCode key, KeyState state);

    /**
     * @brief Gets the current mouse position.
     *
     * @return Position The current position of the mouse cursor.
     */
    Position GetMousePosition();

    /**
     * @brief Gets the current mouse X-coordinate.
     *
     * @return double The X-coordinate of the mouse cursor.
     */
    double GetMouseX();

    /**
     * @brief Gets the current mouse Y-coordinate.
     *
     * @return double The Y-coordinate of the mouse cursor.
     */
    double GetMouseY();

private:
    /**
     * @brief A map to store key event callbacks.
     *
     * This structure maps `KeyCode` to `KeyState`, allowing for efficient
     * O(1) insertion and retrieval of callback functions for key events.
     * Each key can have multiple associated callbacks for different states.
     */
    std::unordered_map<KeyCode, std::unordered_map<KeyState, std::vector<std::function<void()>>>> m_eventKeyCallbacks;

    /**
     * @brief Stores the current position of the mouse cursor.
     */
    Position m_mousePosition;
};

