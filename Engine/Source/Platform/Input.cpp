#include "Platform/Input.h"

#include "Platform/Context.h"

#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace Source::Platform
{
    static void DispatchKey(GLFWwindow* InHandle, int InKey, int, int InAction, int)
    {
        if (InKey < 0)
        {
            return;
        }

        static_cast<Context*>(glfwGetWindowUserPointer(InHandle))->InputPtr->OnKey(InKey, InAction);
    }

    static void DispatchMouseButton(GLFWwindow* InHandle, int InButton, int InAction, int)
    {
        if (InButton < 0)
        {
            return;
        }

        static_cast<Context*>(glfwGetWindowUserPointer(InHandle))->InputPtr->OnMouseButton(InButton, InAction);
    }

    static void DispatchCursorPos(GLFWwindow* InHandle, double InX, double InY)
    {
        static_cast<Context*>(glfwGetWindowUserPointer(InHandle))->InputPtr->OnCursorPos(InX, InY);
    }

    static void DispatchScroll(GLFWwindow* InHandle, double, double InY)
    {
        static_cast<Context*>(glfwGetWindowUserPointer(InHandle))->InputPtr->OnScroll(InY);
    }

    void Input::Bind(void* Handle)
    {
        glfwSetKeyCallback((GLFWwindow*)Handle, &DispatchKey);
        glfwSetMouseButtonCallback((GLFWwindow*)Handle, &DispatchMouseButton);
        glfwSetCursorPosCallback((GLFWwindow*)Handle, &DispatchCursorPos);
        glfwSetScrollCallback((GLFWwindow*)Handle, &DispatchScroll);
    }

    void Input::Read()
    {
        Released.fill(false);
        Pressed.fill(false);

        MouseReleased.fill(false);
        MousePressed.fill(false);

        LastMousePosX = MousePosX;
        LastMousePosY = MousePosY;
        Scroll = 0.0;
    }

    void Input::OnKey(int InKey, int InAction)
    {
        if (InKey >= KeyCount)
        {
            return;
        }

        if (InAction == GLFW_PRESS)
        {
            Pressed[InKey] = true;
            Held[InKey] = true;
        }
        else if (InAction == GLFW_RELEASE)
        {
            Released[InKey] = true;
            Held[InKey] = false;
        }
    }

    bool Input::IsPressed(Key InKey) const
    {
        return Held[(uint16)InKey];
    }

    bool Input::WasPressedThisFrame(Key InKey) const
    {
        return Pressed[(uint16)InKey];
    }

    bool Input::WasReleasedThisFrame(Key InKey) const
    {
        return Released[(uint16)InKey];
    }

    void Input::OnMouseButton(int InButton, int InAction)
    {
        if (InButton >= MouseButtonCount) return;

        if (InAction == GLFW_PRESS)
        {
            MousePressed[InButton] = true;
            MouseHeld[InButton] = true;
        }
        else if (InAction == GLFW_RELEASE)
        {
            MouseReleased[InButton] = true;
            MouseHeld[InButton] = false;
        }
    }

    void Input::OnCursorPos(double InX, double InY)
    {
        MousePosX = InX;
        MousePosY = InY;
    }

    void Input::OnScroll(double InY)
    {
        Scroll += InY;
    }

    bool Input::IsPressed(MouseButton InButton) const
    {
        return MouseHeld[(uint8)InButton];
    }

    bool Input::WasPressedThisFrame(MouseButton InButton) const
    {
        return MousePressed[(uint8)InButton];
    }

    bool Input::WasReleasedThisFrame(MouseButton InButton) const
    {
        return MouseReleased[(uint8)InButton];
    }
}