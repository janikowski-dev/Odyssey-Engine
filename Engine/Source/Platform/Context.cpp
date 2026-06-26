#include "Platform/Context.h"

#include <GLFW/glfw3.h>

namespace Source::Platform
{
    void Context::Register(void* Handle)
    {
        glfwSetWindowUserPointer((GLFWwindow*)Handle, this);
    }
}