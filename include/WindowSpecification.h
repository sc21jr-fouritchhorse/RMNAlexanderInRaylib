//
// Created by qiaojun on 10/02/24.
//

#ifndef WINDOWSPECIFICATION_H
#define WINDOWSPECIFICATION_H
#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>
#include "../include/ECSDefs.h"

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
    namespace Events::Window
    {
        const EventID QUIT = "Events::Window::QUIT"_hash;
        const EventID INPUT = "Events::Window::INPUT"_hash;
        const EventID RESIZE = "Events::Window::RESIZE"_hash;
        namespace Input
        {
            const ParamID INPUT = "Event::Window::Input::INPUT"_hash;
        }
        namespace Resized
        {
            const ParamID WIDTH = "Events::Window::Resized::WIDTH"_hash;
            const ParamID HEIGHT = "Events::Window::Resized::HEIGHT"_hash;
        }
    }
;



#endif //WINDOWSPECIFICATION_H
