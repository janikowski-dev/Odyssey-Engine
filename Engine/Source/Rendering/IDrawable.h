#pragma once

namespace Source::Rendering
{
    class IDrawable
    {
    public:
        virtual ~IDrawable() = default;

        virtual void Draw() const = 0;
    };
}
