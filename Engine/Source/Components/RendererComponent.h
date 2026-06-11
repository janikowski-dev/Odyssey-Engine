#pragma once

#include "../Rendering/Shader.h"
#include "../Rendering/Mesh.h"
#include "../Core/Types.h"

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
            { "shader", R.ShaderId },
            { "mesh", R.MeshId },
            { "color", R.Color }
        };
    }

    inline void from_json(const Json& J, RendererComponent& R)
    {
        R.ShaderId = J.at("shader").get<std::string>();
        R.MeshId = J.at("mesh").get<std::string>();
        R.Color = J.at("color").get<glm::vec3>();
    }
}
