#pragma once

#include <Singleton.h>

class Application : public Singleton<Application>
{
public:
    bool Init();
    void Update(double deltaTime = 0);
};

