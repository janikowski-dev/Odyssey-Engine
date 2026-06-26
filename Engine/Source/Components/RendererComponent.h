#pragma once

#include "Rendering/Material.h"
#include "Rendering/Drawables/Mesh.h"
#include "Core/Minimal.h"

namespace Source::Components
{
    struct COMPONENT RendererComponent
    {
        PROPERTY() std::string MaterialId;
        PROPERTY() std::string MeshId;
    };
}
