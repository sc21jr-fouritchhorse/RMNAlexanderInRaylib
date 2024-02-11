#include <iostream>
#include "ECS/coordinator.h"
#include "Simulation/Components/WindowData.h"
#include "Simulation/Systems/WindowSystem.h"

bool running = true;

int main() {
    Coordinator coordinator;
    WindowSystem windowSystem;

    coordinator.Init();

    coordinator.RegisterComponent<Resolution>();
    coordinator.RegisterComponent<WinPos>();
    coordinator.RegisterComponent<WinTitle>();
    coordinator.RegisterComponent<ContextSpecs>();

    Entity myWindow = coordinator.CreateEntity();

    coordinator.AddComponent<Resolution>(myWindow, { 800, 600 });
    coordinator.AddComponent<WinPos>(myWindow, { 0, 0 });
    coordinator.AddComponent<WinTitle>(myWindow, { "My Window", &myWindow, nullptr });
    coordinator.AddComponent<ContextSpecs>(myWindow, { false, true, 4, 6 });


    windowSystem.Init();

    while (running) {
        windowSystem.Update();
    }

    return 0;
}
