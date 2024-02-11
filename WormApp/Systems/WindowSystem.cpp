//
// Created by qiaojun on 10/02/24.
//
#include "WindowSystem.h"

#include "../Data/WindowSpecification.h"

extern Coordinator gCoordinator;

void WindowSystem::Init()
{
    glfwInit();
    for (auto const& e : mEntities)
    {
        auto& resolution = gCoordinator.GetComponent<Resolution>(e);
        auto& position = gCoordinator.GetComponent<WinPos>(e);
        auto& title = gCoordinator.GetComponent<WinTitle>(e);
        auto& context = gCoordinator.GetComponent<ContextSpecs>(e);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context.majVer);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context.minVer);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, context.resizeable);
        glfwWindowHint(GLFW_FOCUSED, context.focused);
        title.owner = &e;
        title.winRef = glfwCreateWindow(resolution.width, resolution.height,
        title.title.c_str(), nullptr, nullptr);
    }
    gCoordinator.AddEventListener(METHOD_LISTENER(Events::Window::RESIZE, WindowSystem::ResChangeListener));
}

void WindowSystem::Exit()
{
    glfwTerminate();
}

void WindowSystem::Input()
{

}

void WindowSystem::Update()
{
    for (auto const &e : mEntities)
    {
        gCoordinator.GetComponent<>(e);
    }
}





