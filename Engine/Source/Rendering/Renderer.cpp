#include "Renderer.h"

#include "Shader.h"
#include "Mesh.h"

#include "../Components/CameraComponent.h"

#include <glad/gl.h>

namespace Source::Rendering
{
    void Renderer::Begin(const Components::CameraComponent& InCamera)
    {
        Begin();
        CacheCamera(InCamera);
    }

    void Renderer::DrawMesh(const glm::mat4& InModel, const Mesh& InMesh, const Shader& InShader, const glm::vec3& InColor)
    {
        InShader.Use();
        InShader.SetMat4("uView", View);
        InShader.SetMat4("uProj", Projection);
        InShader.SetMat4("uModel", InModel);
        InShader.SetVec3("uColor", InColor);
        InMesh.Draw();
    }

    void Renderer::End()
    {
        glUseProgram(0);
    }

    void Renderer::Begin()
    {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.10f, 0.11f, 0.13f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::CacheCamera(const Components::CameraComponent &InCamera)
    {
        Projection = InCamera.Projection();
        View = InCamera.View();
    }
}
