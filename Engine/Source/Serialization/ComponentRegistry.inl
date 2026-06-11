#pragma once

#include "ComponentRegistry.h"

#include "../ECS/Registry.h"
#include "../ECS/Entity.h"

namespace Source::Serialization
{
    template<typename T>
    void ComponentRegistry::Register(const std::string& Name)
    {
        TypeOps Ops;

        Ops.Save = [Name](ECS::Registry& World, ECS::Entity E, Json& Out) -> bool
        {
            if (World.Has<T>(E))
            {
                Out[Name] = World.Get<T>(E);
                return true;
            }
            
            return false;
        };

        Ops.Load = [](ECS::Registry& World, ECS::Entity E, const Json& Value)
        {
            World.Add<T>(E, Value.get<T>());
        };

        Ops.Collect = [](ECS::Registry& World, std::vector<ECS::Entity>& Out)
        {
            World.View<T>([&](ECS::Entity E, T&) { Out.push_back(E); });
        };

        Types[Name] = std::move(Ops);
    }
}
