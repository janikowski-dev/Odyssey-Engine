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
        glm::vec3 Color { 1.0f };

        // Engine
        Rendering::Shader* Shader = nullptr;
        Rendering::Mesh* Mesh = nullptr;
    };

    inline void to_json(Json& J, const RendererComponent& R)
    {
        J = Json {
            { "Shader", R.ShaderId },
            { "Mesh", R.MeshId },
            { "Color", R.Color }
        };
    }

    inline void from_json(const Json& J, RendererComponent& R)
    {
        R.ShaderId = J.at("Shader").get<std::string>();
        R.MeshId = J.at("Mesh").get<std::string>();
        R.Color = J.at("Color").get<glm::vec3>();
    }
}
