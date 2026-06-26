#include "Rendering/Passes/GridPass.h"

#include "Rendering/Drawables/Procedural.h"
#include "Rendering/Renderer.h"
#include "Rendering/Backend.h"

namespace Source::Rendering
{
    GridPass::GridPass(Core::Context& InContext) : ContextPtr(&InContext)
    {
    }

    GridPass::~GridPass() = default;

    void GridPass::Execute(Backend& InBackend)
    {
        Rendering::Procedural Grid(6);
        InBackend.Draw(Rendering::Renderer(ContextPtr->ResourceCache->Materials.Get("Grid"), &Grid));
    }
}