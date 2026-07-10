#include "Rendering/Texture.h"

#include <glad/gl.h>

namespace Source::Rendering
{
    Texture::Texture(const unsigned char* Data, const int& Width, const int& Height, const int& Channels)
    {
        glGenTextures(1, &Id);
        glBindTexture(GL_TEXTURE_2D, Id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture::~Texture()
    {
        Release();
    }

    Texture::Texture(Texture&& Other) noexcept
    {
        Copy(Other);
        Invalidate(Other);
    }

    Texture& Texture::operator=(Texture&& Other) noexcept
    {
        Release();
        Invalidate(*this);
        Copy(Other);
        Invalidate(Other);
        return *this;
    }

    void Texture::Bind(uint32 Unit) const
    {
        glActiveTexture(GL_TEXTURE0 + Unit);
        glBindTexture(GL_TEXTURE_2D, Id);
    }

    void Texture::Release()
    {
        if (Id)
        {
            glDeleteTextures(1, &Id);
        }
    }

    void Texture::Invalidate(Texture& Texture)
    {
        Texture.Id = 0;
    }

    void Texture::Copy(Texture& Other)
    {
        Id = Other.Id;
    }
}