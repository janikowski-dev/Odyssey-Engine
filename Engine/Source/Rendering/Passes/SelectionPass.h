#pragma once

#include "Rendering/IRenderPass.h"
#include "Rendering/IRenderPass.h"

namespace Source::Core { struct Context; }

namespace Source::Rendering
{
    class Material;

    class SelectionPass : public IRenderPass
    {
    public:
        SelectionPass(Core::Context& InContext);
        ~SelectionPass();

        void Execute(Backend& InBackend) override;

    private:
        Rendering::Material* MaterialPtr;
        Core::Context* ContextPtr;
    };
}
