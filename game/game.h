#pragma once

#include <functional>
#include <project_definitions.h>

class Game
{
public:
    void Init();
    void Update();
    void BindAction();
    void BindKeyAction(KeyCode key, KeyState state, std::function<void()> callback);
    void BindMouseAction(MouseKeyCode mouseKey, KeyState state, std::function<void()> callback);
    void BindMouseMoveAction(std::function<void(int,int)> callback);
};
