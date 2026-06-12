#pragma once

#include "Rendering/Shader.h"
#include "Rendering/Mesh.h"
#include "Core/Minimal.h"

namespace Source::Components
{
    struct COMPONENT RendererComponent
    {
        PROPERTY() std::string ShaderId;
        PROPERTY() std::string MeshId;
        PROPERTY() Vector3 Color { 1.0f };

        Rendering::Shader* Shader = nullptr;
        Rendering::Mesh* Mesh = nullptr;
    };
}
