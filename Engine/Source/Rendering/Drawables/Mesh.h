#pragma once

#include "Rendering/IDrawable.h"
#include "Core/Minimal.h"

namespace Source::Rendering
{
    struct Vertex
    {
        Vector3 Position;
        Vector3 Normal;
    };

    class Mesh : public IDrawable
    {
    public:
        Mesh(const std::vector<Vertex>& Vertices, const std::vector<uint32>& Indices);
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh(Mesh&& Other) noexcept;
        Mesh& operator=(Mesh&& Other) noexcept;

        void Draw() const override;

    private:
        void Release();
        void Invalidate(Mesh& Mesh);
        void Copy(Mesh& Other);

    private:
        uint32 IndexCount = 0;
        uint32 Vao = 0;
        uint32 Vbo = 0;
        uint32 Ebo = 0;
    };
}
