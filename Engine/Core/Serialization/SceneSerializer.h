#pragma once

#include "ComponentRegistry.h"

#include "../Types.h"

#include <string>

namespace Core::Scene
{
    class SceneSerializer
    {
    public:
        explicit SceneSerializer(const ComponentRegistry& InRegistry) : Registry(InRegistry) {}

        Json Save(ECS::Registry& World) const;
        void Load(const Json& Scene, ECS::Registry& World) const;

        bool SaveToFile(ECS::Registry& World, const std::string& Path) const;
        bool LoadFromFile(const std::string& Path, ECS::Registry& World) const;

    private:
        const ComponentRegistry& Registry;
        static constexpr int Version = 1;
    };
}