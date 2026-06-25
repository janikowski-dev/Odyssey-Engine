#pragma once

#include "Core/Minimal.h"

struct GLFWwindow;

namespace Source::Platform
{
    enum class Key : uint16
    {
        // Printable
        Space = 32, Apostrophe = 39, Comma = 44, Minus = 45, Period = 46, Slash = 47,
        Num0 = 48, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        Semicolon = 59, Equal = 61,
        A = 65, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        LeftBracket = 91, Backslash = 92, RightBracket = 93, GraveAccent = 96,

        // Navigation / editing
        Escape = 256, Enter = 257, Tab = 258, Backspace = 259, Insert = 260, Delete = 261,
        Right = 262, Left = 263, Down = 264, Up = 265,
        PageUp = 266, PageDown = 267, Home = 268, End = 269,
        CapsLock = 280, ScrollLock = 281, NumLock = 282, PrintScreen = 283, Pause = 284,

        // Function
        F1 = 290, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

        // Keypad
        KP0 = 320, KP1, KP2, KP3, KP4, KP5, KP6, KP7, KP8, KP9,
        KPDecimal = 330, KPDivide = 331, KPMultiply = 332,
        KPSubtract = 333, KPAdd = 334, KPEnter = 335, KPEqual = 336,

        // Modifiers
        LeftShift = 340, LeftControl = 341, LeftAlt = 342, LeftSuper = 343,
        RightShift = 344, RightControl = 345, RightAlt = 346, RightSuper = 347,
        Menu = 348,
    };

    enum class MouseButton : uint8
    {
        Left = 0, Right = 1, Middle = 2,
        Button4 = 3, Button5 = 4, Button6 = 5, Button7 = 6, Button8 = 7,
    };

    class Input
    {
    public:
        void Bind(void* Handle);
        void Read();

        bool IsPressed(Key InKey) const;
        bool WasPressedThisFrame(Key InKey) const;
        bool WasReleasedThisFrame(Key InKey) const;

        bool IsPressed(MouseButton InButton) const;
        bool WasPressedThisFrame(MouseButton InButton) const;
        bool WasReleasedThisFrame(MouseButton InButton) const;

        void OnKey(int InKey, int InAction);

        float MouseX() const { return (float)MousePosX; }
        float MouseY() const { return (float)MousePosY; }
        float MouseDeltaX() const { return (float)(MousePosX - LastMousePosX); }
        float MouseDeltaY() const { return (float)(MousePosY - LastMousePosY); }
        float ScrollDelta() const { return (float)Scroll; }

        void OnMouseButton(int InButton, int InAction);
        void OnCursorPos(double InX, double InY);
        void OnScroll(double InY);

    private:
        static constexpr uint8  MouseButtonCount = 8;
        static constexpr uint16 KeyCount = 349;

        std::array<bool, KeyCount> Released{};
        std::array<bool, KeyCount> Pressed{};
        std::array<bool, KeyCount> Held{};

        std::array<bool, MouseButtonCount> MouseReleased{};
        std::array<bool, MouseButtonCount> MousePressed{};
        std::array<bool, MouseButtonCount> MouseHeld{};

        double LastMousePosX = 0.0, LastMousePosY = 0.0;
        double MousePosX = 0.0, MousePosY = 0.0;
        double Scroll = 0.0;
    };
}