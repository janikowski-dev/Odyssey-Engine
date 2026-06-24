#include "Modules/WorldModule.h"

#include "ECS/Registry.h"

namespace Source::Modules
{
    void WorldModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.World = MakeUnique<ECS::Registry>();
    }
}