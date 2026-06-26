#include "Rendering/Passes/GridPass.h"

#include "Rendering/Drawables/Procedural.h"
#include "Rendering/Renderer.h"
#include "Rendering/Backend.h"

namespace Source::Rendering
{
    GridPass::GridPass(Core::Context& InContext) : ContextPtr(&InContext), GridPtr(&Rendering::Procedural(6))
    {
    }

    GridPass::~GridPass() = default;

    void GridPass::Execute(Backend& InBackend)
    {
        InBackend.Draw(Rendering::Renderer(ContextPtr->ResourceCache->Materials.Get("Grid"), GridPtr));
    }
}