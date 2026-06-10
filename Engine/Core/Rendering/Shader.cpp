#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <utility>

namespace Core::Rendering
{
    GLuint Shader::Compile(GLenum Stage, const char* Source)
    {
        GLuint Id = glCreateShader(Stage);
        glShaderSource(Id, 1, &Source, nullptr);
        glCompileShader(Id);

        GLint Ok = GL_FALSE;

        glGetShaderiv(Id, GL_COMPILE_STATUS, &Ok);

        if (!Ok)
        {
            GLchar Log[1024];
            glGetShaderInfoLog(Id, sizeof(Log), nullptr, Log);
            std::cerr << "[Shader] compile failed: " << Log << "\n";
        }

        return Id;
    }

    Shader::Shader(const char* VertexSource, const char* FragmentSource)
    {
        GLuint Vs = Compile(GL_VERTEX_SHADER, VertexSource);
        GLuint Fs = Compile(GL_FRAGMENT_SHADER, FragmentSource);

        Program = glCreateProgram();
        glAttachShader(Program, Vs);
        glAttachShader(Program, Fs);
        glLinkProgram(Program);

        GLint Ok = GL_FALSE;
        glGetProgramiv(Program, GL_LINK_STATUS, &Ok);

        if (!Ok)
        {
            GLchar Log[1024];
            glGetProgramInfoLog(Program, sizeof(Log), nullptr, Log);
            std::cerr << "[Shader] link failed: " << Log << "\n";
        }

        glDeleteShader(Vs);
        glDeleteShader(Fs);
    }

    Shader::~Shader()
    {
        if (Program)
        {
            glDeleteProgram(Program);
        }
    }

    Shader::Shader(Shader&& Other) noexcept : Program(Other.Program)
    {
        Other.Program = 0;
    }

    Shader& Shader::operator=(Shader&& Other) noexcept
    {
        if (this != &Other)
        {
            if (Program) glDeleteProgram(Program);
            Program = Other.Program;
            Other.Program = 0;
        }

        return *this;
    }

    void Shader::Use() const
    {
        glUseProgram(Program);
    }

    void Shader::SetMat4(const char* Name, const glm::mat4& Value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(Program, Name), 1, GL_FALSE, glm::value_ptr(Value));
    }

    void Shader::SetVec3(const char* Name, const glm::vec3& Value) const
    {
        glUniform3fv(glGetUniformLocation(Program, Name), 1, glm::value_ptr(Value));
    }
}
