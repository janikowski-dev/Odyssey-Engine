#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace Core::Rendering
{
    class Shader
    {
    public:
        Shader(const char* VertexSource, const char* FragmentSource);
        ~Shader();

        void SetMat4(const char* Name, const glm::mat4& Value) const;
        void SetVec3(const char* Name, const glm::vec3& Value) const;

        void Use() const;

    private:
        static GLuint Compile(GLenum Stage, const char* Source);

    private:
        GLuint Program = 0;
    };
}
