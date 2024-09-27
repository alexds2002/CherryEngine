#pragma once

#include <Singleton.h>
#include <memory>

class Window;

class Application : public Singleton<Application>
{
public:
    Application();
    ~Application();
    bool Init();
    void Update(double deltaTime = 0);
private:
    std::unique_ptr<Window> m_window;
};

