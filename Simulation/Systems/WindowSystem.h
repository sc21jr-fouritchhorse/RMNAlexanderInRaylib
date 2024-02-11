#ifndef WINDOW_SYSTEM_H
#define WINDOW_SYSTEM_H
#include "../Components/WindowData.h"
#include "../../ECS/Core/System.h"

class WindowSystem : public System
{
public:
    void Init();
    void Update();

};

#endif // WINDOW_SYSTEM_H