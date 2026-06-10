#pragma once

#include "../Types.h"

#include <glad/gl.h>
#include <glm/glm.hpp>

#include <cstdint>
#include <vector>

namespace Core::Rendering
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
    };

    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& Vertices, const std::vector<uint32>& Indices);
        ~Mesh();

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
