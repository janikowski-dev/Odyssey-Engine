#include "Modules/ResourcesModule.h"

namespace Source::Modules
{
    void ResourcesModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        InitCache(Context);
        LoadResources(Config, Context);
    }
    
    void ResourcesModule::InitCache(Core::Context& Context)
    {
        Context.ResourceCache = MakeUnique<Resources::ResourceCache>();
    }

    void ResourcesModule::LoadResources(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.ResourceCache->Refresh(Config.EngineConfig.GetStaticResourcesPath());
        Context.ResourceCache->Refresh(Config.EngineConfig.GetProjectResourcesPath());
    }
}
