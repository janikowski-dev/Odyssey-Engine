#pragma once

#include "Rendering/IRenderPass.h"

namespace Source::Core { struct Context; }

namespace Source::Rendering
{
    class Procedural;
    class Material;

    class GridPass : public IRenderPass
    {
    public:
        GridPass(Core::Context& InContext);
        ~GridPass();

        void Execute(Backend& InBackend) override;

    private:
        Rendering::Procedural* ProceduralPtr;
        Rendering::Material* MaterialPtr;
    };
}
