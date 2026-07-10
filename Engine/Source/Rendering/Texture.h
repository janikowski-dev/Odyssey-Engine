#pragma once

#include "Core/Minimal.h"

namespace Source::Rendering
{
    class Texture
    {
    public:
        Texture(const unsigned char* Data, const int& Width, const int& Height, const int& Channels);
        ~Texture();

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
        Texture(Texture&& Other) noexcept;
        Texture& operator=(Texture&& Other) noexcept;

        void Bind(uint32 Unit = 0) const;

    private:
        void Release();
        void Invalidate(Texture& Texture);
        void Copy(Texture& Other);

    private:
        uint32 Id = 0;
    };
}