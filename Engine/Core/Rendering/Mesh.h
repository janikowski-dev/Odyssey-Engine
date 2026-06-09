#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include <cstdint>
#include <vector>

namespace Core::Renderer
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
    };

    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& Vertices, const std::vector<std::uint32_t>& Indices);
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh(Mesh&& Other) noexcept;
        Mesh& operator=(Mesh&& Other) noexcept;

        void Draw() const;

        static Mesh Cube();

    private:
        void Release();

    private:
        GLsizei IndexCount = 0;
        GLuint Vao = 0;
        GLuint Vbo = 0;
        GLuint Ebo = 0;
    };
}
