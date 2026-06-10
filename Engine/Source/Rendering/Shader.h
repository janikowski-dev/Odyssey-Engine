#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

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

        void SetMat4(const char* Name, const glm::mat4& Value) const;
        void SetVec3(const char* Name, const glm::vec3& Value) const;

    private:
        static GLuint Compile(GLenum Stage, const char* Source);

    private:
        GLuint Program = 0;
    };
}
