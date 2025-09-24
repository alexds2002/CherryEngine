#include "runtime.h"

#include <input_manager.h>
#include "../core/render/renderer2D.h"

Runtime::Runtime(const std::shared_ptr<Renderer2D>& renderer2D) : m_renderer2D(renderer2D)
{
}

bool Runtime::Init()
{
    return true; // success
}

void Runtime::Update(float deltaTime)
{
}

void Runtime::BindKeyAction(KeyCode key, KeyState state, std::function<void()> callback)
{
    InputManager::GetInstance()->BindAction(key, state, callback);
}

void Runtime::BindMouseAction(MouseKeyCode mouseKey, KeyState state, std::function<void()> callback)
{
    InputManager::GetInstance()->BindMouseEvent(mouseKey, state, callback);
}

void Runtime::BindMouseMoveAction(std::function<void(int,int)> callback)
{
    InputManager::GetInstance()->BindToMouseMove(callback);
}
