#pragma once

#include "Core/Minimal.h"

namespace Source::Components { struct CameraComponent; struct TransformComponent; }

namespace Source::Rendering
{
    class Shader;
    class Mesh;

    class Renderer
    {
    public:
        void Begin(const Components::CameraComponent& InCamera);
        void DrawMesh(const Components::TransformComponent& InModel, const Mesh& InMesh, const Shader& InShader, const Vector3& InColor);
        void End();

    private:
        void Begin();
        void CacheCamera(const Components::CameraComponent& InCamera);

    private:
        glm::mat4 View { 1.0f };
        glm::mat4 Projection { 1.0f };
    };
}
