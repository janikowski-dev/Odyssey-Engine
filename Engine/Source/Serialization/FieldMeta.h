#pragma once

#include <optional>
#include <string>
#include <vector>

namespace Source::Serialization
{
    struct FieldMeta
    {
        std::vector<std::string> Options;
        std::optional<double> Min;
        std::optional<double> Max;
    };
}