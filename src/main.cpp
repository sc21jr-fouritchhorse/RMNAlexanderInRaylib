//
// Created by qiaojun on 10/02/24.
//
#include "ecsCoordinator.h"
#include "WindowSpecification.h"
#include "WindowSystem.h"

Coordinator globalCoordinator;
static bool running = true;

// void QuitHandler(Event &e)
// {
//     running = false;
// }

int main()
{
    globalCoordinator.Init();

    Entity myWindow = globalCoordinator.CreateEntity();
    globalCoordinator.AddComponent<ContextSpecs>(myWindow, ContextSpecs{false, true, 4, 5});
    globalCoordinator.AddComponent<Resolution>(myWindow, Resolution{800, 600});
    globalCoordinator.AddComponent<WinPos>(myWindow, WinPos{0, 0});
    globalCoordinator.AddComponent<WinTitle>(myWindow, {"Hello ECS", nullptr, nullptr});

    auto winSys = globalCoordinator.RegisterSystem<WindowSystem>();
    {
        Signature winSysSig;
        winSysSig.set(globalCoordinator.GetComponentType<Resolution>());
        winSysSig.set(globalCoordinator.GetComponentType<WinPos>());
        winSysSig.set(globalCoordinator.GetComponentType<WinTitle>());
    }

    winSys->Init();

    while (running)
    {
        winSys->Input();
        winSys->Update();
    }

    winSys->Exit();

    return 0;
}
