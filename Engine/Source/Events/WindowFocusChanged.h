#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view WindowFocusChangedKey = "window_focus_changed";

    struct WindowFocusChanged
    {
        bool IsFocused;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WindowFocusChanged, IsFocused);
}