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

    void Source::Modules::ResourcesModule::Tick(const Core::Context &Context)
    {
        Context.World->View<Components::RendererComponent>(
            [&Context](ECS::Entity, Components::RendererComponent& R)
            {
                R.Shader = Context.ResourceCache->Shaders.Get(R.ShaderId);
                R.Mesh = Context.ResourceCache->Meshes.Get(R.MeshId);
            }
        );
    }

}
