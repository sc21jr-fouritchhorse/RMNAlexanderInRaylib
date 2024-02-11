//
// Created by qiaojun on 10/02/24.
//
#include <GLFW/glfw3.h>
#include "WindowSystem.h"
#include "WindowSpecification.h"
#include "ecsCoordinator.h"

extern Coordinator gCoordinator;

void WindowSystem::Init() const
{
    glfwInit();
    for (auto const& e : mEntities)
    {
        auto& [width, height] = gCoordinator.GetComponent<Resolution>(e);
        auto& [title, owner, winRef] = gCoordinator.GetComponent<WinTitle>(e);
        auto& [resizeable, focused, majVer, minVer] = gCoordinator.GetComponent<ContextSpecs>(e);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majVer);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minVer);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, resizeable);
        glfwWindowHint(GLFW_FOCUSED, focused);
        owner = &e;
        winRef = glfwCreateWindow(width, height,
            title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(winRef);
    }
}

void WindowSystem::Exit()
{
    glfwTerminate();
}

void WindowSystem::Input()
{
    glfwPollEvents();
}

void WindowSystem::Update()
{
    for (auto const &e : mEntities)
    {
        GLFWwindow* currentWin = gCoordinator.GetComponent<WinTitle>(e).winRef;
        glfwSwapBuffers(currentWin);
    }
}







