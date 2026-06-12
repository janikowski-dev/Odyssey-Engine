#pragma once

#include "FieldMeta.h"

#include "Core/Minimal.h"
#include "ECS/Entity.h"

#include <functional>
#include <string>
#include <vector>

namespace Source::Serialization
{
    struct FieldInfo
    {
        std::function<void(void*, const Json&)> Set;
        std::function<Json(const void*)> Get;
        std::string Name;
        std::string Type;
        FieldMeta Meta;
    };

    using ComponentResolver = std::function<void*(ECS::Entity)>;
    using ComponentEmplacer = std::function<void*(ECS::Entity)>;

    struct TypeInfo
    {
        std::vector<FieldInfo> Fields;
        ComponentResolver Resolve;
        ComponentEmplacer Emplace;
        std::string Name;
    };
}
