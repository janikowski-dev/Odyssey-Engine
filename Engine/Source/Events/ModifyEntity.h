#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view ModifyEntityKey = "modify_entity";

    struct ModifyEntityRequest
    {
        std::string Component;
        uint32 Index;
        Json Fields;
    };

    struct ModifyEntityResponse
    {
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ModifyEntityRequest, Component, Index, Fields);
}