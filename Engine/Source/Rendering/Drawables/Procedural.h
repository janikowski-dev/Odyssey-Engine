#pragma once

#include "Rendering/IDrawable.h"
#include "Core/Minimal.h"

namespace Source::Rendering
{
    class Procedural : public IDrawable
    {
    public:
        Procedural(int InVertexCount);
        ~Procedural();

        Procedural(const Procedural&) = delete;
        Procedural& operator=(const Procedural&) = delete;
        Procedural(Procedural&& Other) noexcept;
        Procedural& operator=(Procedural&& Other) noexcept;

        void Draw() const override;

    private:
        void Release();
        void Invalidate(Procedural& Procedural);
        void Copy(Procedural& Other);
        
    private:
        uint32 EmptyVao = 0;
        int VertexCount;
    };
}