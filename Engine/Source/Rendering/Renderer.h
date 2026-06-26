#pragma once

#include "Core/Minimal.h"

namespace Source::Rendering
{
    class IDrawable;
    class Material;

    class Renderer
    {
    public:
        Renderer(Material* InMaterialPtr, IDrawable* InDrawablePtr);

    public:
        IDrawable* DrawablePtr = nullptr;
        Material* MaterialPtr = nullptr;
    };
}