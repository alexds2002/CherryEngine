#pragma once

#include <singleton.h>
#include <memory>

class Window;
class Game;
class Renderer2D;
class ResourceManager;
struct Position;

/**
 * @file Application.h
 * @brief Main application class for managing the application lifecycle.
 *
 * This class serves as the central component of the application, providing functionality
 * to initialize and update the application state. It is designed as a singleton to ensure
 * that only one instance of the application exists throughout its lifecycle.
 *
 * The `Application` class manages a window through the `Window` class, which is responsible
 * for creating and handling a GLFW window.
 *
 * Potential Example Usage:
 * @code
 * Application& app = Application::GetInstance();
 * if (app.Init()) {
 *     double deltaTime = 0.0;
 *     while (running) {
 *         app.Update(deltaTime);
 *     }
 * }
 * @endcode
 */

class Application : public Singleton<Application>
{
public:
    /**
     * @brief Constructor for the Application class.
     *
     * This constructor initializes any necessary resources for the application.
     * It sets up the singleton instance.
     */
    Application();

    /**
     * @brief Destructor for the Application class.
     *
     * This destructor cleans up any resources allocated during the application's lifetime,
     * including the window instance.
     */
    ~Application();

    /**
     * @brief Initializes the application.
     *
     * This function sets up the application environment, including creating the window and
     * initializing any necessary subsystems.
     *
     * @return true if initialization is successful; false otherwise.
     */
    bool Init();

    /**
     * @brief Updates the application state.
     *
     * This function updates the application logic. It can be called every frame to perform
     * necessary calculations and render updates.
     *
     * @param deltaTime Time in seconds since the last update. Defaults to 0 if not specified.
     */
    void Update(double deltaTime = 0);

private:
    /**
     * @brief Unique pointer to the Window instance.
     *
     * This member variable manages the window's lifecycle and allows the application to interact
     * with the GLFW window created within the Window class.
     */
    std::unique_ptr<Window> m_window;

    std::unique_ptr<Game> m_game;

    std::unique_ptr<ResourceManager> m_rssManager;

    std::shared_ptr<Renderer2D> m_renderer2D;
};
