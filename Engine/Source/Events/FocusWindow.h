#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view FocusWindowKey = "focus_window";

    struct FocusWindowRequest
    {
    };

    struct FocusWindowResponse
    {
    };
}