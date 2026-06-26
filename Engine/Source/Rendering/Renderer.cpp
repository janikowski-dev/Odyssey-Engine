#include "Rendering/Renderer.h"

#include "Rendering/IDrawable.h"
#include "Rendering/Material.h"

namespace Source::Rendering
{
    Renderer::Renderer(Material* InMaterialPtr, IDrawable* InDrawablePtr) : MaterialPtr(InMaterialPtr), DrawablePtr(InDrawablePtr)
    {
    }
}