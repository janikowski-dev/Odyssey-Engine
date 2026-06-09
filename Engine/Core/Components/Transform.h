#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Core::Components
{
    struct Transform
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
}
