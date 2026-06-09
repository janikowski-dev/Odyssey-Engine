#include "Mesh.h"

#include <utility>

namespace Core::Rendering
{
    Mesh::Mesh(const std::vector<Vertex>& Vertices, const std::vector<std::uint32_t>& Indices) : IndexCount(static_cast<GLsizei>(Indices.size()))
    {
        glGenVertexArrays(1, &Vao);
        glGenBuffers(1, &Vbo);
        glGenBuffers(1, &Ebo);

        glBindVertexArray(Vao);

        glBindBuffer(GL_ARRAY_BUFFER, Vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(Vertices.size() * sizeof(Vertex)), Vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(Indices.size() * sizeof(std::uint32_t)), Indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, Position)));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, Normal)));

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
        Vao = Vbo = Ebo = 0;
        IndexCount = 0;
    }

    Mesh::~Mesh()
    {
        Release();
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

    Mesh Mesh::Cube()
    {
        const glm::vec3 P[8] = {
            {-0.5f,-0.5f,-0.5f}, { 0.5f,-0.5f,-0.5f}, { 0.5f, 0.5f,-0.5f}, {-0.5f, 0.5f,-0.5f},
            {-0.5f,-0.5f, 0.5f}, { 0.5f,-0.5f, 0.5f}, { 0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f},
        };

        struct Face
        {
            int a, b, c, d;
            glm::vec3 n;
        };

        const Face F[6] = {
            {4,5,6,7, { 0, 0, 1}}, {1,0,3,2, { 0, 0,-1}},
            {0,4,7,3, {-1, 0, 0}}, {5,1,2,6, { 1, 0, 0}},
            {3,7,6,2, { 0, 1, 0}}, {0,1,5,4, { 0,-1, 0}},
        };

        std::vector<Vertex> Vertices;
        std::vector<std::uint32_t> Indices;

        for (const Face& f : F)
        {
            std::uint32_t base = static_cast<std::uint32_t>(Vertices.size());
            Vertices.push_back({ P[f.a], f.n });
            Vertices.push_back({ P[f.b], f.n });
            Vertices.push_back({ P[f.c], f.n });
            Vertices.push_back({ P[f.d], f.n });
            Indices.insert(Indices.end(), { base, base + 1, base + 2, base, base + 2, base + 3 });
        }

        return Mesh(Vertices, Indices);
    }
}
