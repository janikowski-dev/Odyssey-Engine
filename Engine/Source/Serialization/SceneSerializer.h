#pragma once

#include "Core/Minimal.h"

#include <string>

namespace Source::ECS { class Registry; }

namespace Source::Serialization
{
    class SceneSerializer
    {
    public:
        bool SaveToFile(ECS::Registry& World, const std::string& Path) const;
        bool LoadFromFile(const std::string& Path, ECS::Registry& World) const;
    };
}
