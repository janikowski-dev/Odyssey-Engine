#include "Rendering/Transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Source::Rendering
{
    Transform::Transform(const Vector3& Position, const Vector3& Rotation, const Vector3& Scale)
    {
        Matrix = glm::translate(Matrix, Position);
        Matrix = glm::rotate(Matrix, glm::radians(Rotation.x), Vector3(1, 0, 0));
        Matrix = glm::rotate(Matrix, glm::radians(Rotation.y), Vector3(0, 1, 0));
        Matrix = glm::rotate(Matrix, glm::radians(Rotation.z), Vector3(0, 0, 1));
        Matrix = glm::scale(Matrix, Scale);
    }
}