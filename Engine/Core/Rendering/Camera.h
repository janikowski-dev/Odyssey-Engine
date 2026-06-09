#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Core::Renderer
{
    struct Camera
    {
        glm::vec3 Position { 0.0f, 2.0f, 6.0f };
        glm::vec3 Target { 0.0f, 0.0f, 0.0f };
        glm::vec3 Up { 0.0f, 1.0f, 0.0f };

        float FovDegrees = 60.0f;
        float Aspect = 16.0f / 9.0f;
        float Near = 0.1f;
        float Far = 100.0f;

        glm::mat4 View() const
        {
            return glm::lookAt(Position, Target, Up);
        }
        
        glm::mat4 Projection() const
        {
            return glm::perspective(glm::radians(FovDegrees), Aspect, Near, Far);
        }
    };
}
