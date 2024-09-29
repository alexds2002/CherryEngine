#include "input_manager.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <project_definitions.h>
#include <debug_assert_component.h>

// TODO(Alex): Add modifications support.
static void HandleKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    InputManager::GetInstance()->DispatchKeyEvent(static_cast<KeyCode>(key), static_cast<KeyState>(action));
}

static void HandleMouseEvent(GLFWwindow* window, int mouse_button, int action, int mods)
{
    InputManager::GetInstance()->DispatchKeyEvent(static_cast<KeyCode>(mouse_button), static_cast<KeyState>(action));
}

static void HandleMouseMoveEvent(GLFWwindow* window, double xpos, double ypos)
{
}

InputManager::InputManager()
{
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

Position InputManager::GetMousePosition()
{
    return m_mousePosition;
}

double InputManager::GetMouseX()
{
    return m_mousePosition.x;
}

double InputManager::GetMouseY()
{
    return m_mousePosition.y;
}

