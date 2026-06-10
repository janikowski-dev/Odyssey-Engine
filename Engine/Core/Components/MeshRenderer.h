#pragma once

#include "../Rendering/Mesh.h"
#include "../Types.h"

#include <glm/glm.hpp>
#include <memory>

namespace glm
{
    inline void to_json(Core::Json& J, const glm::vec3& V)
    {
        J = Core::Json::array({ V.x, V.y, V.z });
    }

    inline void from_json(const Core::Json& J, glm::vec3& V)
    {
        V.x = J.at(0).get<float>();
        V.y = J.at(1).get<float>();
        V.z = J.at(2).get<float>();
    }
}

namespace Core::Components
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
