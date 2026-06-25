#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace Source::Platform
{
    class Context
    {
    public:
        void Register(void* Handle);

    public:
        class Window* WindowPtr = nullptr;
        class Input* InputPtr = nullptr;
    };
}