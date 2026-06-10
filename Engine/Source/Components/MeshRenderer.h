#pragma once

#include "../Rendering/Mesh.h"
#include "../Core/Types.h"

namespace Source::Components
{
    struct MeshRenderer
    {
        glm::vec3 Color { 1.0f };
    };

    inline void to_json(Json& J, const MeshRenderer& R)
    {
        J = Json {
            { "color", R.Color }
        };
    }

    inline void from_json(const Json& J, MeshRenderer& R)
    {
        R.Color = J.at("color").get<glm::vec3>();
    }
}
