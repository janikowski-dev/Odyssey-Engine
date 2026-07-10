#include "Rendering/Material.h"

#include "Rendering/Texture.h"
#include "Rendering/Shader.h"

namespace Source::Rendering
{
    Material::Material(Shader* InShader) : ShaderPtr(InShader)
    {
    }

    void Material::Set(const char* Name, float Value)
    {
        Floats[Name] = Value;
    }

    void Material::Set(const char* Name, const Vector3& Value)
    {
        Vectors[Name] = Value;
    }

    void Material::Set(const char* Name, const Matrix4& Value)
    {
        Matrices[Name] = Value;
    }

    void Material::Set(const char* Name, Texture* Value)
    {
        Textures[Name] = Value;
    }

    void Material::Bind() const
    {
        ShaderPtr->Use();

        for (const auto& [Name, Value] : Floats)
        {
            ShaderPtr->Set(Name.c_str(), Value);
        }

        for (const auto& [Name, Value] : Vectors)
        {
            ShaderPtr->Set(Name.c_str(), Value);
        }

        for (const auto& [Name, Value] : Matrices)
        {
            ShaderPtr->Set(Name.c_str(), Value);
        }

        int Unit = 0;

        for (const auto& [Name, Value] : Textures)
        {
            Value->Bind(Unit);
            ShaderPtr->Set(Name.c_str(), Unit++);
        }
    }

    void Material::Use() const
    {
        ShaderPtr->Use();
    }

    void Material::SetSoft(const char* Name, float Value) const
    {
        ShaderPtr->Set(Name, Value);
    }

    void Material::SetSoft(const char* Name, const Vector3& Value) const
    {
        ShaderPtr->Set(Name, Value);
    }

    void Material::SetSoft(const char* Name, const Matrix4& Value) const
    {
        ShaderPtr->Set(Name, Value);
    }
}
