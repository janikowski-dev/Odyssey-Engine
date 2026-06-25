#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view SentMessageKey = "sent_message";

    struct SentMessage
    {
        std::string Content;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SentMessage, Content);
}