#pragma once

#include "Rendering/Drawables/Procedural.h"
#include "Rendering/IRenderPass.h"
#include "Core/Context.h"

namespace Source::Rendering
{
    class Material;
    class Backend;

    class GridPass : public IRenderPass
    {
    public:
        GridPass(Core::Context& InContext);
        ~GridPass();

        void Execute(Backend& InBackend) override;

    private:
        Material* MaterialPtr;
        Procedural Grid;
    };
}
