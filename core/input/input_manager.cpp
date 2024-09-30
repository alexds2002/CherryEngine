#include "input_manager.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

/* TODO(Alex): Add modifications support. */

/**
 * @brief Handles keyboard events from the GLFW window.
 *
 * This function is called by GLFW when a key event occurs (e.g., key pressed, released).
 * It retrieves the key code and action and dispatches the corresponding event to
 * the `InputManager`, which will handle the registered callbacks for that key.
 * The event handling functions must be non member functions (free functions) as required from glfw.
 *
 * @param window A pointer to the GLFW window that received the event.
 * @param key The key code of the key that was pressed or released.
 * @param scancode The system-specific scancode of the key.
 * @param action The action of the event (e.g., GLFW_PRESS, GLFW_RELEASE).
 * @param mods Bitfield that indicates which modifier keys were held down
 *             during the event (e.g., Shift, Ctrl).
 *
 * @note This function must be registered with GLFW using
 *       `glfwSetKeyCallback()` to ensure it is called on key events.
 */
static void HandleKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    InputManager::GetInstance()->DispatchKeyEvent(static_cast<KeyCode>(key), static_cast<KeyState>(action));
}

/**
 * @brief Handles mouse button events from the GLFW window.
 *
 * This function is called by GLFW when a mouse button event occurs (e.g., button pressed, released).
 * It retrieves the mouse button code and action, then dispatches the corresponding event to
 * the `InputManager`, which will handle the registered callbacks for that mouse button.
 *
 * @param window A pointer to the GLFW window that received the event.
 * @param mouse_button The mouse button code of the button that was pressed or released.
 * @param action The action of the event (e.g., GLFW_PRESS, GLFW_RELEASE).
 * @param mods Bitfield that indicates which modifier keys were held down
 *             during the event (e.g., Shift, Ctrl).
 *
 * @note This function must be registered with GLFW using
 *       `glfwSetMouseButtonCallback()` to ensure it is called on mouse button events.
 */
static void HandleMouseEvent(GLFWwindow* window, int mouse_button, int action, int mods)
{
    InputManager::GetInstance()->DispatchKeyEvent(static_cast<KeyCode>(mouse_button), static_cast<KeyState>(action));
}

/**
 * @brief Handles mouse movement events from the GLFW window.
 *
 * This function is called by GLFW when the mouse is moved. Currently, it does not
 * dispatch any events but can be expanded to handle mouse movement in the future.
 *
 * @param window A pointer to the GLFW window that received the event.
 * @param xpos The new X-coordinate of the mouse cursor.
 * @param ypos The new Y-coordinate of the mouse cursor.
 *
 * @note This function can be registered with GLFW using
 *       `glfwSetCursorPosCallback()` if mouse movement needs to be tracked.
 *       Currently, no actions are performed within this function.
 */
static void HandleMouseMoveEvent(GLFWwindow* window, double xpos, double ypos)
{
    // Currently, no actions are performed within this function.
    // TODO(Alex): update mouse position value here
}

void InputManager::Init(GLFWwindow* window)
{
    glfwSetKeyCallback(window, HandleKeyEvent);
    glfwSetMouseButtonCallback(window, HandleMouseEvent);
    glfwSetCursorPosCallback(window, HandleMouseMoveEvent);
}

void InputManager::PollEvents()
{
    glfwPollEvents();
}

/**
 * @brief Dispatches all callbacks associated with a specific key and state.
 *
 * This function checks if there are any registered callbacks for the given
 * key (`KeyCode`) and state (`KeyState`). If such callbacks exist, they are
 * executed in the order they were registered. If no callbacks are found for
 * the key or state, the function does nothing and returns early.
 *
 * @param key The `KeyCode` representing the key that was pressed or released.
 * @param state The `KeyState` representing the state of the key (e.g., CHERRY_PRESS, CHERRY_RELEASE).
 *
 * @details
 * - The function first looks up the `key` in the `m_eventKeyCallbacks` map.
 *   If no entry exists for the key, it returns immediately.
 * - If the `key` exists, it then checks if there are any callbacks for the
 *   specific `state` (e.g., pressed or released). If no callbacks exist for
 *   that state, it returns immediately.
 * - If callbacks are found, it loops through the list of callbacks and invokes
 *   each one in the order they were registered.
 *
 * Example usage:
 * @code
 * inputManager.DispatchKeyEvent(W_KEY, KEY_PRESSED);
 * @endcode
 */

void InputManager::DispatchKeyEvent(KeyCode key, KeyState state)
{
    auto state_maps = m_eventKeyCallbacks.find(key);
    if(state_maps == m_eventKeyCallbacks.end()) return;

    auto current_state_map = state_maps->second.find(state);
    if(current_state_map == state_maps->second.end()) return;
    auto& callbacks = current_state_map->second;
    for(auto& callback : callbacks)
    {
        callback();
    }
}

/**
 * @brief Binds a callback function to a specific key and state.
 *
 * This function registers a callback function that will be executed when a
 * specific key (`KeyCode`) is in a given state (`KeyState`). Multiple
 * callbacks can be bound to the same key and state, and they will be
 * executed in the order they were registered.
 *
 * @param key The `KeyCode` representing the key to bind the action to
 *            (e.g., `CHERRY_KEY_W`, `CHERRY_KEY_A`).
 * @param state The `KeyState` representing the state of the key (e.g.,
 *              `CHERRY_PRESS`, `CHERRY_RELEASE`, `CHERRY_REPEAT`).
 * @param callback A `std::function<void()>` representing the callback
 *                 function to be executed when the key and state match.
 *
 * @details
 * - The function allows multiple callbacks to be registered for the same key and state.
 * - When the key is in the specified state (e.g., pressed or released), the
 *   associated callback will be triggered.
 * - The callback is stored internally in the `m_eventKeyCallbacks` map, which
 *   holds a vector of callbacks for each combination of `KeyCode` and `KeyState`.
 *
 * Example usage:
 * @code
 *  InputManager::GetInstance()->BindAction(KeyCode::CHERRY_KEY_W, KeyState::CHERRY_REPEAT, [](){ Debug_Log("Hi"); });
 *  InputManager::GetInstance()->BindAction(KeyCode::CHERRY_KEY_W, KeyState::CHERRY_PRESS, [](){ Debug_Log("Not hi"); });
 * @endcode
 *
 * @see InputManager::DispatchKeyEvent for how these callbacks are executed.
 */
void InputManager::BindAction(KeyCode key, KeyState state, std::function<void()> callback)
{
    m_eventKeyCallbacks[key][state].push_back(callback);
}

/**
 * @brief Retrieves the current mouse position as a Position object.
 *
 * This function returns the current position of the mouse cursor
 * as a `Position` structure containing the X and Y coordinates.
 *
 * @return Position The current mouse position.
 */
Position InputManager::GetMousePosition()
{
    return m_mousePosition;
}

/**
 * @brief Retrieves the current X coordinate of the mouse cursor.
 *
 * This function returns the X coordinate of the current mouse cursor position.
 *
 * @return double The current X coordinate of the mouse.
 */
double InputManager::GetMouseX()
{
    return m_mousePosition.x;
}

/**
 * @brief Retrieves the current Y coordinate of the mouse cursor.
 *
 * This function returns the Y coordinate of the current mouse cursor position.
 *
 * @return double The current Y coordinate of the mouse.
 */
double InputManager::GetMouseY()
{
    return m_mousePosition.y;
}
