#include "Rendering/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Source::Rendering
{
    Camera::Camera(const Vector3& Position, const Vector3& Rotation, const float& FovDegrees, const float& Aspect, const float& Near, const float& Far)
    {
        Projection = glm::perspective(glm::radians(FovDegrees), Aspect, Near, Far);

        Matrix4 World(1.0f);
        World = glm::translate(World, Position);
        World = glm::rotate(World, glm::radians(Rotation.y), Vector3(0, 1, 0));
        World = glm::rotate(World, glm::radians(Rotation.x), Vector3(1, 0, 0));
        World = glm::rotate(World, glm::radians(Rotation.z), Vector3(0, 0, 1));

        View = glm::inverse(World);
    }
}