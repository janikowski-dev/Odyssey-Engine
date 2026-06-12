#pragma once

#include "Core/Minimal.h"
#include "ECS/Entity.h"

namespace Source::Serialization
{
    Json GetComponentTypes();
    Json GetComponents(ECS::Entity Entity);
    void SetComponent(ECS::Entity Entity, const std::string& Type, const Json& Fields);
}
