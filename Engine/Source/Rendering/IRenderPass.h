#pragma once

namespace Source::Rendering
{
    class Backend;

    class IRenderPass
    {
    public:
        virtual ~IRenderPass() = default;

        virtual void Execute(Backend& Backend) = 0;
    };
}
