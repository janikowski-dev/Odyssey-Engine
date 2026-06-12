#include "SceneSerializer.h"

#include "../ECS/Registry.h"

#include <fstream>

namespace Source::Serialization
{
    bool SceneSerializer::SaveToFile(ECS::Registry& World, const std::string& Path) const
    {
        return true;
    }

    bool SceneSerializer::LoadFromFile(const std::string& Path, ECS::Registry& World) const
    {
        return true;
    }
}
