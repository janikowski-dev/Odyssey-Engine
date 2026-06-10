#pragma once

#include "../Rendering/Mesh.h"
#include "../Types.h"

#include <glm/glm.hpp>
#include <memory>

namespace Core::Components
{
    struct MeshRenderer
    {
        SharedPtr<Rendering::Mesh> Mesh;
        glm::vec3 Color { 1.0f };
    };
}
