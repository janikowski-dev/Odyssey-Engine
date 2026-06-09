#pragma once

#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"

#include <glm/glm.hpp>

namespace Core::Rendering
{
    class Renderer
    {
    public:
        Renderer();

        void SetCamera(const Camera& InCamera) { Camera = InCamera; }
        void SetViewport(int Width, int Height);

        void Begin();
        void DrawMesh(const glm::mat4& Model, const Mesh& InMesh, const glm::vec3& Color);
        void End();

    private:
        Shader DefaultShader;
        Camera Camera;
    };
}
