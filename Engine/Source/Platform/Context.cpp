#include "Platform/Context.h"

namespace Source::Platform
{
    void Context::Register(void* Handle)
    {
        glfwSetWindowUserPointer((GLFWwindow*)Handle, this);
    }
}