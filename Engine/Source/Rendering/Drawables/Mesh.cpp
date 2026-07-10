#include "Rendering/Drawables/Mesh.h"

#include <glad/gl.h>

namespace Source::Rendering
{
    Mesh::Mesh(const std::vector<Vertex>& Vertices, const std::vector<uint32>& Indices) : IndexCount(static_cast<GLsizei>(Indices.size()))
    {
        glGenVertexArrays(1, &Vao);
        glGenBuffers(1, &Vbo);
        glGenBuffers(1, &Ebo);

        glBindVertexArray(Vao);

        glBindBuffer(GL_ARRAY_BUFFER, Vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(Vertices.size() * sizeof(Vertex)), Vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(Indices.size() * sizeof(uint32)), Indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, Position)));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, Normal)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, UV)));

        glBindVertexArray(0);
    }

    Mesh::~Mesh()
    {
        Release();
    }

    Mesh::Mesh(Mesh&& Other) noexcept
    {
        Copy(Other);
        Invalidate(Other);
    }

    Mesh& Mesh::operator=(Mesh&& Other) noexcept
    {
        Release();
        Invalidate(*this);
        Copy(Other);
        Invalidate(Other);
        return *this;
    }

    void Mesh::Draw() const
    {
        glBindVertexArray(Vao);
        glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    void Mesh::Release()
    {
        if (Vbo)
        {
            glDeleteBuffers(1, &Vbo);
        }

        if (Ebo)
        {
            glDeleteBuffers(1, &Ebo);
        }

        if (Vao)
        {
            glDeleteVertexArrays(1, &Vao);
        }
    }
    
    void Mesh::Invalidate(Mesh& Mesh)
    {
        Mesh.Vao = Mesh.Vbo = Mesh.Ebo = 0;
        Mesh.IndexCount = 0;
    }

    void Mesh::Copy(Mesh& Other)
    {
        IndexCount = Other.IndexCount;
        Vao = Other.Vao;
        Vbo = Other.Vbo;
        Ebo = Other.Ebo;
    }
}
