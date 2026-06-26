#include "Modules/ResourcesModule.h"

namespace Source::Modules
{
    void ResourcesModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.ResourceCache = MakeUnique<Resources::ResourceCache>(Config.EngineConfig.GetResourcesPath());
        Context.ResourceCache->Refresh();
    }
}
