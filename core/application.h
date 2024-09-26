#pragma once

#include <Singleton.h>

class Window;

class Application : public Singleton<Application>
{
public:
    Application();
    ~Application();
    bool Init();
    void Update(double deltaTime = 0);
private:
    Window* m_window;
};

