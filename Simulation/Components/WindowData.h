#pragma once

#include "../../ECS/ecsDefinitions.h"
#include <string>
#include <GLFW/glfw3.h>

struct Resolution {
    uint32_t width;
    uint32_t height;
};

struct WinPos
{
    uint32_t x;
    uint32_t y;
};

struct WinTitle{
    std::string const& title;
    const Entity* owner;
    GLFWwindow* winRef;
};

struct ContextSpecs{
    bool resizeable;
    bool focused;
    uint32_t majVer;
    uint32_t minVer;
};