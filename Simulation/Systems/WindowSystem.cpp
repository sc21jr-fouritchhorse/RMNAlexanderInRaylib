#include "WindowSystem.h"
#include "../../ECS/coordinator.h"

extern Coordinator gCoordinator;

void WindowSystem::Init()
{
    for (auto& entity : entities)
    {
        Resolution resolution = gCoordinator.GetComponent<Resolution>(entity);
        WinPos position = gCoordinator.GetComponent<WinPos>(entity);
        WinTitle title =  gCoordinator.GetComponent<WinTitle>(entity);
        ContextSpecs contextSpecs = gCoordinator.GetComponent<ContextSpecs>(entity);

        // Create GLFW window
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextSpecs.majVer);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextSpecs.minVer);
        glfwWindowHint(GLFW_RESIZABLE, contextSpecs.resizeable);
        glfwWindowHint(GLFW_FOCUSED, contextSpecs.focused);

        GLFWwindow* window = glfwCreateWindow(resolution.width, resolution.height, title.title.c_str(), nullptr, nullptr);
        if (window == nullptr)
        {
            glfwTerminate();
        }

        title.winRef = window;

        // Subscribe to the window component
        gCoordinator.AddComponent<WinTitle>(entity, title);
    }
}

void WindowSystem::Update()
{
    for (auto& entity : entities)
    {
        //swap buffers for every window entity
        WinTitle title = gCoordinator.GetComponent<WinTitle>(entity);
        glfwSwapBuffers(title.winRef);
    }
}
