#pragma once

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