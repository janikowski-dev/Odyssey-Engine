#include "Modules/PlatformModule.h"

#include "Platform/Window.h"

namespace Source::Modules
{
    void PlatformModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.Window = MakeUnique<Platform::Window>(Config.WindowConfig);
        Context.Window->Create(*Context.EditorBridge);
    }

    void PlatformModule::Tick(const Core::Context& Context)
    {
        Context.Window->Refresh();
    }
}