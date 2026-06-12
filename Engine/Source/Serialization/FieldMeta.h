#pragma once

#include "Core/Minimal.h"

namespace Source::Serialization
{
    struct FieldMeta
    {
        std::vector<std::string> Options;
        std::optional<double> Min;
        std::optional<double> Max;
    };
}