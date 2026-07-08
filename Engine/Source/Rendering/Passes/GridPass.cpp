#include "Rendering/Passes/GridPass.h"

#include "Rendering/Drawables/Procedural.h"
#include "Rendering/Renderer.h"
#include "Rendering/Backend.h"
#include "Core/Context.h"

#include <glad/gl.h>

namespace Source::Rendering
{
    GridPass::GridPass(Core::Context& InContext) : MaterialPtr(InContext.ResourceCache->Materials.Get("Grid")), ProceduralPtr(InContext.ResourceCache->Procedurals.Get("Grid"))
    {
    }

    GridPass::~GridPass() = default;

    void GridPass::Execute(Backend& InBackend)
    {
        glDisable(GL_CULL_FACE);
        InBackend.Draw(Rendering::Renderer(MaterialPtr, ProceduralPtr));
        glEnable(GL_CULL_FACE);
    }
}