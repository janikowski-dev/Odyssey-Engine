#pragma once

#include "Core/Minimal.h"

namespace Source::ECS { class Registry; }

namespace Source::Serialization
{
    bool SaveScene(ECS::Registry& World, const std::string& Path);
    bool LoadScene(ECS::Registry& World, const std::string& Path);

    bool SaveScene(const std::string& Path, const Json& Out);
    bool LoadScene(const std::string& Path, Json& In);

    void SerializeScene(ECS::Registry& World, Json& Scene);
    void DeserializeScene(ECS::Registry& World, const Json& Scene);
}