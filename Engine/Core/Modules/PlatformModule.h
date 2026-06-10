#pragma once

#include "../IModule.h"
#include "../Platform/Window.h"

namespace Core
{
    class PlatformModule final : public IModule
    {
    public:
        PlatformModule() = default;
        ~PlatformModule() override = default;

        void Init(const ApplicationConfig Config, Context& Context) override
        {
		    Context.Window = MakeUnique<Platform::Window>(Config.WindowConfig);
		    Context.Window->Create(*Context.EditorBridge);
        }

        void Tick(const Context& Context) override
        {
			Context.Window->Tick();
        }
    };
}