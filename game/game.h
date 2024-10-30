#pragma once

#include <functional>
#include <project_definitions.h>
#include <memory>

class Renderer2D;

/**
 * @class Game
 * @brief Manages the runtime of the game engine, including initialization, updates, and input handling.
 *
 * The Game class serves as the core runtime class for the game engine. It initializes the game,
 * manages the update cycle, and provides a framework for handling input through bindable actions.
 * The class is meant to provide abstraction from the core of the engine.
 * This class requires a Renderer2D object for rendering purposes, which is injected via dependency injection.
 */
class Game
{
public:
    /**
     * @brief Constructs the Game with a Renderer2D dependency.
     *
     * @param renderer2D A shared pointer to a Renderer2D instance, used for rendering operations.
     */
    explicit Game(const std::shared_ptr<Renderer2D>& renderer2D);

    /**
     * @brief Initializes the game and its components.
     *
     * @return true if initialization succeeds, false otherwise.
     */
    bool Init();

    /**
     * @brief Executes one update cycle of the game, including logic updates and rendering.
     */
    void Update();

    /**
     * @brief Binds a key action to a specified key and key state.
     *
     * @param key The key code for the keyboard key to bind.
     * @param state The key state (e.g., pressed, released) to trigger the action.
     * @param callback The function to execute when the key and state match.
     */
    void BindKeyAction(KeyCode key, KeyState state, std::function<void()> callback);

    /**
     * @brief Binds a mouse action to a specified mouse button and key state.
     *
     * @param mouseKey The key code for the mouse button to bind.
     * @param state The key state (e.g., pressed, released) to trigger the action.
     * @param callback The function to execute when the mouse button and state match.
     */
    void BindMouseAction(MouseKeyCode mouseKey, KeyState state, std::function<void()> callback);

    /**
     * @brief Binds an action to mouse movement events.
     *
     * @param callback A function that takes the x and y positions of the mouse and executes when the mouse moves.
     */
    void BindMouseMoveAction(std::function<void(int, int)> callback);

private:
    /**
     * @brief A shared pointer to the Renderer2D instance, responsible for rendering operations.
     */
    std::shared_ptr<Renderer2D> m_renderer2D;
};
