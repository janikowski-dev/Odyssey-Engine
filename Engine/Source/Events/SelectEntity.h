#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view SelectEntityKey = "select_entity";

    struct SelectEntityRequest
    {
        uint32 Index;
    };

    struct SelectEntityResponse
    {
        Json Data;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SelectEntityRequest, Index);
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SelectEntityResponse, Data);
}