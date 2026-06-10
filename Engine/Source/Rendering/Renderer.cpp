#include "Renderer.h"

#include <glad/gl.h>

namespace Source::Rendering
{
    namespace
    {
        const char* DefaultVertex = R"(#version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aNormal;
            
        uniform mat4 uModel;
        uniform mat4 uView;
        uniform mat4 uProj;
            
        out vec3 vNormal;
            
        void main()
        {
            vNormal = mat3(transpose(inverse(uModel))) * aNormal;
            gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
        }
        )";

        const char* DefaultFragment = R"(#version 330 core
        in vec3 vNormal;
        uniform vec3 uColor;
        out vec4 FragColor;

        void main()
        {
            vec3 N = normalize(vNormal);
            vec3 L = normalize(vec3(0.4, 1.0, 0.6));
            float diff = max(dot(N, L), 0.0);
            vec3 c = uColor * (0.25 + 0.75 * diff);
            FragColor = vec4(c, 1.0);
        }
        )";
    }

    Renderer::Renderer() : DefaultShader(DefaultVertex, DefaultFragment)
    {
    }

    void Renderer::SetViewport(int Width, int Height)
    {
        glViewport(0, 0, Width, Height);

        if (Height > 0)
        {
            Camera.Aspect = static_cast<float>(Width) / static_cast<float>(Height);
        }
    }

    void Renderer::Begin()
    {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.10f, 0.11f, 0.13f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        DefaultShader.Use();
        DefaultShader.SetMat4("uView", Camera.View());
        DefaultShader.SetMat4("uProj", Camera.Projection());
    }

    void Renderer::DrawMesh(const glm::mat4& Model, const Mesh& InMesh, const glm::vec3& Color)
    {
        DefaultShader.SetMat4("uModel", Model);
        DefaultShader.SetVec3("uColor", Color);
        InMesh.Draw();
    }

    void Renderer::End()
    {
        glUseProgram(0);
    }
}
