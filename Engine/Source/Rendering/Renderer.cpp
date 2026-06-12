#include "Rendering/Renderer.h"

#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
#include "Rendering/Shader.h"
#include "Rendering/Mesh.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Source::Rendering
{
    void Renderer::Begin(const Components::CameraComponent& InCamera)
    {
        Begin();
        CacheCamera(InCamera);
    }

    void Renderer::DrawMesh(const Components::TransformComponent& InModel, const Mesh& InMesh, const Shader& InShader, const Vector3& InColor)
    {
        glm::mat4 Matrix(1.0f);

        Matrix = glm::translate(Matrix, InModel.Position);
        Matrix = glm::rotate(Matrix, InModel.Rotation.x, Vector3(1, 0, 0));
        Matrix = glm::rotate(Matrix, InModel.Rotation.y, Vector3(0, 1, 0));
        Matrix = glm::rotate(Matrix, InModel.Rotation.z, Vector3(0, 0, 1));
        Matrix = glm::scale(Matrix, InModel.Scale);

        InShader.Use();
        InShader.SetMat4("uView", View);
        InShader.SetMat4("uProj", Projection);
        InShader.SetMat4("uModel", Matrix);
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
        Projection = glm::perspective(glm::radians(InCamera.FovDegrees), InCamera.Aspect, InCamera.Near, InCamera.Far);
        View = glm::lookAt(InCamera.Position, InCamera.Target, InCamera.Up);
    }
}
