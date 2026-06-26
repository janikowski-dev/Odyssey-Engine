#include "Modules/WorldModule.h"

namespace Source::Modules
{
    void WorldModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.World = MakeUnique<ECS::Registry>();
    }
}