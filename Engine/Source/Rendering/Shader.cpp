#include "Rendering/Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <glad/gl.h>

namespace Source::Rendering
{
    Shader::Shader(const char* VertexSource, const char* FragmentSource)
    {
        GLuint Vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(Vs, 1, &VertexSource, nullptr);
        glCompileShader(Vs);
        
        GLuint Fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(Fs, 1, &FragmentSource, nullptr);
        glCompileShader(Fs);

        Program = glCreateProgram();
        glAttachShader(Program, Vs);
        glAttachShader(Program, Fs);
        glLinkProgram(Program);

        glDeleteShader(Vs);
        glDeleteShader(Fs);
    }

    Shader::~Shader()
    {
        Release();
    }

    Shader::Shader(Shader&& Other) noexcept
    {
        Copy(Other);
        Invalidate(Other);
    }

    Shader& Shader::operator=(Shader&& Other) noexcept
    {
        Release();
        Copy(Other);
        Invalidate(Other);
        return *this;
    }

    void Shader::Use() const
    {
        glUseProgram(Program);
    }

    void Shader::Set(const char* Name, const float& Value) const
    {
        glUniform1f(glGetUniformLocation(Program, Name), Value);
    }

    void Shader::Set(const char* Name, const Matrix4& Value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(Program, Name), 1, GL_FALSE, glm::value_ptr(Value));
    }

    void Shader::Set(const char* Name, const Vector3& Value) const
    {
        glUniform3fv(glGetUniformLocation(Program, Name), 1, glm::value_ptr(Value));
    }

    
    void Shader::Release()
    {
        if (Program)
        {
            glDeleteProgram(Program);
        }
    }
    
    void Shader::Invalidate(Shader& Shader)
    {
        Shader.Program = 0;
    }

    void Shader::Copy(Shader& Other)
    {
        Program = Other.Program;
    }
}
