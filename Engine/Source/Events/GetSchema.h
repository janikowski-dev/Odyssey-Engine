#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view GetSchemaKey = "get_schema";

    struct GetSchemaRequest
    {
    };

    struct GetSchemaResponse
    {
        Json Schema;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetSchemaResponse, Schema);
}