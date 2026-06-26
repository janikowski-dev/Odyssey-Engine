#pragma once

#include "Core/Minimal.h"

namespace Source::Rendering
{
    class Shader;

    class Material
    {
    public:
        explicit Material(Shader* InShader);

        void Bind() const;

        void Set(const char* Name, float Value);
        void Set(const char* Name, const Vector3& Value);
        void Set(const char* Name, const Matrix4& Value);

        void Use() const;
        void SetSoft(const char* Name, float Value) const;
        void SetSoft(const char* Name, const Vector3& Value) const;
        void SetSoft(const char* Name, const Matrix4& Value) const;

    private:
        std::unordered_map<std::string, Matrix4> Matrices;
        std::unordered_map<std::string, Vector3> Vectors;
        std::unordered_map<std::string, float> Floats;
        Shader* ShaderPtr = nullptr;
    };
}
