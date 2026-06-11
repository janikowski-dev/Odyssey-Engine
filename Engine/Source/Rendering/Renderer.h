#pragma once

#include <glm/glm.hpp>

namespace Source::Components { class CameraComponent; }

namespace Source::Rendering
{
    class Shader;
    class Mesh;

    class Renderer
    {
    public:
        void Begin(const Components::CameraComponent& InCamera);
        void DrawMesh(const glm::mat4& InModel, const Mesh& InMesh, const Shader& InShader, const glm::vec3& InColor);
        void End();

    private:
        void Begin();
        void CacheCamera(const Components::CameraComponent& InCamera);

    private:
        glm::mat4 View { 1.0f };
        glm::mat4 Projection { 1.0f };
    };
}
