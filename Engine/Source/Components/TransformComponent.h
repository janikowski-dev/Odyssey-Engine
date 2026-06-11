#pragma once

#include "../Core/Minimal.h"

namespace Source::Components
{
    struct TransformComponent
    {
        glm::vec3 Position { 0.0f };
        glm::vec3 Rotation { 0.0f };
        glm::vec3 Scale { 1.0f };

        glm::mat4 Matrix() const
        {
            glm::mat4 M(1.0f);
            M = glm::translate(M, Position);
            M = glm::rotate(M, Rotation.x, glm::vec3(1, 0, 0));
            M = glm::rotate(M, Rotation.y, glm::vec3(0, 1, 0));
            M = glm::rotate(M, Rotation.z, glm::vec3(0, 0, 1));
            M = glm::scale(M, Scale);
            return M;
        }
    };
    
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TransformComponent, Position, Rotation, Scale)
}
