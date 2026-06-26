#pragma once

#include "Rendering/IRenderPass.h"
#include "Core/Context.h"

namespace Source::Rendering
{
    class Procedural;
    class Backend;

    class GridPass : public IRenderPass
    {
    public:
        GridPass(Core::Context& InContext);
        ~GridPass();

        void Execute(Backend& InBackend) override;

    private:
        Core::Context* ContextPtr;
        Procedural* GridPtr;
    };
}
