#pragma once

#include "Core/Minimal.h"

#include <glad/gl.h>

namespace Source::Rendering
{
    struct Vertex
    {
        Vector3 Position;
        Vector3 Normal;
    };

    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& Vertices, const std::vector<uint32>& Indices);
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh(Mesh&& Other) noexcept;
        Mesh& operator=(Mesh&& Other) noexcept;

        void Draw() const;

    private:
        void Release();

    private:
        GLsizei IndexCount = 0;
        GLuint Vao = 0;
        GLuint Vbo = 0;
        GLuint Ebo = 0;
    };
}
