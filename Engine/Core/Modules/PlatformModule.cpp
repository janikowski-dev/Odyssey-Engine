#include "PlatformModule.h"

#include "../Platform/Window.h"

namespace Core::Modules
{
    void PlatformModule::Init(const ApplicationConfig Config, Context& Context)
    {
        Context.Window = MakeUnique<Platform::Window>(Config.WindowConfig);
        Context.Window->Create(*Context.EditorBridge);
    }

    void PlatformModule::Tick(const Context& Context)
    {
        Context.Window->Tick();
    }
}