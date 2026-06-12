#pragma once

#include "Rendering/Shader.h"
#include "Rendering/Mesh.h"
#include "Core/Minimal.h"

namespace Source::Components
{
    struct RendererComponent
    {
        // Serializable
        std::string ShaderId;
        std::string MeshId;
        Vector3 Color { 1.0f };

        // Engine
        Rendering::Shader* Shader = nullptr;
        Rendering::Mesh* Mesh = nullptr;
    };
}
