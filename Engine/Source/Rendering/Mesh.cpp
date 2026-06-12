#include "Rendering/Mesh.h"

#include <utility>

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

        glBindVertexArray(0);
    }

    Mesh::~Mesh()
    {
        Release();
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
        
        Vao = Vbo = Ebo = 0;
        IndexCount = 0;
    }

    Mesh::Mesh(Mesh&& Other) noexcept : Vao(Other.Vao), Vbo(Other.Vbo), Ebo(Other.Ebo), IndexCount(Other.IndexCount)
    {
        Other.Vao = Other.Vbo = Other.Ebo = 0;
        Other.IndexCount = 0;
    }

    Mesh& Mesh::operator=(Mesh&& Other) noexcept
    {
        if (this != &Other)
        {
            Release();
            Vao = Other.Vao; Vbo = Other.Vbo; Ebo = Other.Ebo; IndexCount = Other.IndexCount;
            Other.Vao = Other.Vbo = Other.Ebo = 0;
            Other.IndexCount = 0;
        }

        return *this;
    }

    void Mesh::Draw() const
    {
        glBindVertexArray(Vao);
        glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
}
