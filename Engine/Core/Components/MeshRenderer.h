#pragma once

#include "../Rendering/Mesh.h"

#include <glm/glm.hpp>
#include <memory>

namespace Core::Components
{
    struct MeshRenderer
    {
        std::shared_ptr<Rendering::Mesh> Mesh;
        glm::vec3 Color { 1.0f };
    };
}
