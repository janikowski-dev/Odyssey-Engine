#pragma once

#include "Core/Minimal.h"

namespace Source::Rendering
{
    class IDrawable;
    class Material;

    class Renderer
    {
    public:
        Renderer(Material* InMaterialPtr, IDrawable* InDrawablePtr, const Vector3& InColor = Vector3 { 1.0f });

    public:
        IDrawable* DrawablePtr = nullptr;
        Material* MaterialPtr = nullptr;
        Vector3 Color { 0.0f };
    };
}