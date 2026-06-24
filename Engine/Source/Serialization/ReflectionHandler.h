#pragma once

#include "Core/Minimal.h"

namespace Source::ECS { class Entity; }

namespace Source::Serialization
{
    Json GetComponentTypes();
    Json GetComponents(ECS::Entity Entity);
    void SetComponent(ECS::Entity Entity, const std::string& Type, const Json& Fields);
    void RemoveComponent(ECS::Entity Entity, const std::string& Type);
}
