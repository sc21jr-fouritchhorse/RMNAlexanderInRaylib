//
// Created by qiaojun on 10/02/24.
//

#ifndef WINDOWSYSTEM_H
#define WINDOWSYSTEM_H

#include "../../ECSaustinMorlan/system.h"
#include "../../ECSaustinMorlan/event.h"
#include "../../ECSaustinMorlan/ecsCoordinator.h"

#include "../../deps/glfw-3.3.9/include/GLFW/glfw3.h"
#include <raylib.h>


class WindowSystem : public System
{
public:
    void Init();
    void Exit();
    void Input();
    void Update();
private:
    void ResChangeListener(Event& event);
    std::vector<GLFWwindow*> mWindows;
};


#endif //WINDOWSYSTEM_H
