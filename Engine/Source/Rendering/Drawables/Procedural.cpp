#include "Rendering/Drawables/Procedural.h"

#include <glad/gl.h>

namespace Source::Rendering
{
    Procedural::Procedural(int InVertexCount) : VertexCount(InVertexCount)
    {
        glGenVertexArrays(1, &EmptyVao);
    }

    Procedural::~Procedural()
    {
        Release();
    }

    Procedural::Procedural(Procedural&& Other) noexcept
    {
        Copy(Other);
        Invalidate(Other);
    }

    Procedural& Procedural::operator=(Procedural&& Other) noexcept
    {
        Release();
        Copy(Other);
        Invalidate(Other);
        return *this;
    }

    void Procedural::Draw() const
    {
        glBindVertexArray(EmptyVao);
        glDrawArrays(GL_TRIANGLES, 0, VertexCount);
        glBindVertexArray(0);
    }

    void Procedural::Release()
    {
        if (EmptyVao)
        {
            glDeleteVertexArrays(1, &EmptyVao);
        }
    }

    void Procedural::Invalidate(Procedural& Procedural)
    {
        Procedural.EmptyVao = 0;
    }

    void Procedural::Copy(Procedural& Other)
    {
        EmptyVao = Other.EmptyVao;
    }
}