#pragma once

#include "Rendering/IRenderPass.h"

namespace Source::Core { struct Context; }

namespace Source::Rendering
{
    class MeshPass : public IRenderPass
    {
    public:
        MeshPass(Core::Context& InContext);
        ~MeshPass();

        void Execute(Backend& InBackend) override;

    private:
        Core::Context* ContextPtr;
    };
}
