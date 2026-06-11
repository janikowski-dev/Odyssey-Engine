#pragma once

#include "ComponentRegistry.h"

#include "../Core/Types.h"

#include <string>

namespace Source::ECS { class Registry; }

namespace Source::Serialization
{
    class SceneSerializer
    {
    public:
        explicit SceneSerializer(const ComponentRegistry& InRegistry) : Registry(InRegistry) {}

        bool SaveToFile(ECS::Registry& World, const std::string& Path) const;
        bool LoadFromFile(const std::string& Path, ECS::Registry& World) const;

    private:
        const ComponentRegistry& Registry;
    };
}
