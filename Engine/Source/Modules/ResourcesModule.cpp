#include "Modules/ResourcesModule.h"

#include "Components/RendererComponent.h"
#include "Resources/ResourceCache.h"

namespace Source::Modules
{
    void ResourcesModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.ResourceCache = MakeUnique<Resources::ResourceCache>(Config.EngineConfig.GetResourcesPath());
        Context.ResourceCache->Refresh();
    }
}
