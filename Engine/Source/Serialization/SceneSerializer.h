#pragma once

#include "Core/Minimal.h"

namespace Source::ECS { class Registry; }

namespace Source::Serialization
{
    bool SaveScene(ECS::Registry& World);
    bool LoadScene(ECS::Registry& World);

    void SerializeScene(ECS::Registry& World, Json& Scene);
    void DeserializeScene(ECS::Registry& World, const Json& Scene);
}