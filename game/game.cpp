#include "game.h"

#include <input_manager.h>

void Game::Init()
{
}

void Game::Update()
{
}

void Game::BindKeyAction(KeyCode key, KeyState state, std::function<void()> callback)
{
    InputManager::GetInstance()->BindAction(key, state, callback);
}

void Game::BindMouseAction(MouseKeyCode mouseKey, KeyState state, std::function<void()> callback)
{
    InputManager::GetInstance()->BindMouseEvent(mouseKey, state, callback);
}

void Game::BindMouseMoveAction(std::function<void(int,int)> callback)
{
    InputManager::GetInstance()->BindToMouseMove(callback);
}

