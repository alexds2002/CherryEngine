#include "game.h"

#include <input_manager.h>
#include "../core/render/renderer2D.h"

Game::Game(const std::shared_ptr<Renderer2D>& renderer2D) : m_renderer2D(renderer2D)
{
}

bool Game::Init()
{
    return true; // success
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

