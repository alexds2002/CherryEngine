#pragma once

#include <functional>
#include <project_definitions.h>
#include <memory>

class Renderer2D;

class Game
{
public:
    explicit Game(const std::shared_ptr<Renderer2D>& renderer2D);
    bool Init();
    void Update();
    void BindAction();
    void BindKeyAction(KeyCode key, KeyState state, std::function<void()> callback);
    void BindMouseAction(MouseKeyCode mouseKey, KeyState state, std::function<void()> callback);
    void BindMouseMoveAction(std::function<void(int,int)> callback);

private:
    /* Dependancy Injection */
    std::shared_ptr<Renderer2D> m_renderer2D;
};
