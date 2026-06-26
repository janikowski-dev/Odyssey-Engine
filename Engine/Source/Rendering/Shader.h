#pragma once

#include "Core/Minimal.h"

namespace Source::Rendering
{
    class Shader
    {
    public:
        Shader(const char* VertexSource, const char* FragmentSource);
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader(Shader&& Other) noexcept;
        Shader& operator=(Shader&& Other) noexcept;

        void Use() const;

        void Set(const char* Name, const float& Value) const;
        void Set(const char* Name, const Matrix4& Value) const;
        void Set(const char* Name, const Vector3& Value) const;

    private:
        void Release();
        void Invalidate(Shader& Mesh);
        void Copy(Shader& Other);

    private:
        uint32 Program = 0;
    };
}
