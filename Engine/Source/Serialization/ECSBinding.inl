#pragma once

#include "TypeBuilder.h"

#include "../ECS/Registry.h"
#include "../ECS/Entity.h"

namespace Source::Serialization
{
    template <typename TComponent>
    void BindECS(TypeBuilder<TComponent>& Builder, ECS::Registry& Registry)
    {
        Builder.Bind(
            [&Registry](ECS::Entity E) -> void* { return Registry.TryGet<TComponent>(E); },
            [&Registry](ECS::Entity E) -> void* { return &Registry.GetOrAdd<TComponent>(E); }
        );
    }
};
