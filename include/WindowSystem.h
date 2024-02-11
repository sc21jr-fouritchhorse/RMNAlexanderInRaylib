//
// Created by qiaojun on 10/02/24.
//

#ifndef WINDOWSYSTEM_H
#define WINDOWSYSTEM_H

#include "../include//system.h"
#include "../include/event.h"

class WindowSystem : public System
{
public:
    void Init() const;
    static void Exit();
    static void Input();
    void Update();
private:
    std::vector<GLFWwindow*> mWindows;
};


#endif //WINDOWSYSTEM_H
