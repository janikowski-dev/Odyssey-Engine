#include "Modules/PlatformModule.h"

#include "Platform/Context.h"

namespace Source::Modules
{
    PlatformModule::PlatformModule() = default;
    PlatformModule::~PlatformModule() = default;

    void PlatformModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        InitWindow(Config, Context);
        InitInput(Config, Context);
        InitLocalContext(Config, Context);
    }

    void PlatformModule::Tick(const Core::Context& Context)
    {
        Context.Input->Read();
        Context.Window->Refresh();
    }

    void PlatformModule::InitWindow(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.Window = MakeUnique<Platform::Window>(Config.WindowConfig);
        Context.Window->Create();
    }

    void PlatformModule::InitInput(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.Input = MakeUnique<Platform::Input>();
        Context.Input->Bind(Context.Window->GetHandle());
    }

    void PlatformModule::InitLocalContext(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        LocalContext = MakeUnique<Platform::Context>();
        LocalContext->WindowPtr = Context.Window.get();
        LocalContext->InputPtr = Context.Input.get();
        LocalContext->Register(Context.Window->GetHandle());
    }
}