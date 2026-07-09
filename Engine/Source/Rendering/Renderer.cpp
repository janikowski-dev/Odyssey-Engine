#include "Rendering/Renderer.h"

#include "Rendering/IDrawable.h"
#include "Rendering/Material.h"

namespace Source::Rendering
{
    Renderer::Renderer(Material* InMaterialPtr, IDrawable* InDrawablePtr, const Vector3& InColor) : MaterialPtr(InMaterialPtr), DrawablePtr(InDrawablePtr), Color(InColor)
    {
    }
}