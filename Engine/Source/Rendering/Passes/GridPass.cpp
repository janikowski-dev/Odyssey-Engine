#include "Rendering/Passes/GridPass.h"

#include "Rendering/Renderer.h"
#include "Rendering/Backend.h"

namespace Source::Rendering
{
    GridPass::GridPass(Core::Context& InContext) : MaterialPtr(InContext.ResourceCache->Materials.Get("Grid")), Grid(6)
    {
    }

    GridPass::~GridPass() = default;

    void GridPass::Execute(Backend& InBackend)
    {
        InBackend.Draw(Rendering::Renderer(MaterialPtr, &Grid));
    }
}