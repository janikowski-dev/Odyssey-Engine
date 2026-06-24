#include "Modules/WorldModule.h"

#include "Messages/DestroyedEntityMessage.h"
#include "Messages/CreatedEntityMessage.h"
#include "Messaging/MessageBus.h"
#include "ECS/Registry.h"

namespace Source::Modules
{
    void WorldModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.World = MakeUnique<ECS::Registry>();

        Context.World->OnEntityDestroyed += [&Context](uint32 Index)
        {
            Context.MessageBus->Enqueue(Messages::DestroyedEntityMessage { Index });
        };

        Context.World->OnEntityCreated += [&Context](uint32 Index)
        {
            Context.MessageBus->Enqueue(Messages::CreatedEntityMessage { Index });
        };
    }
}