#pragma once

#include "../ECS/Registry.h"
#include "../Types.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Core::Serialization
{
    class ComponentRegistry
    {
    public:
        template<typename T>
        void Register(const std::string& Name);

        void Save(ECS::Registry& World, ECS::Entity E, Json& Out) const;
        void Load(ECS::Registry& World, ECS::Entity E, const Json& Data) const;
        std::vector<ECS::Entity> CollectEntities(ECS::Registry& World) const;

    private:
        struct TypeOps
        {
            std::function<bool(ECS::Registry&, ECS::Entity, Json&)> Save;
            std::function<void(ECS::Registry&, ECS::Entity, const Json&)> Load;
            std::function<void(ECS::Registry&, std::vector<ECS::Entity>&)> Collect;
        };

        std::unordered_map<std::string, TypeOps> Types;
    };
}

#include "ComponentRegistry.inl"