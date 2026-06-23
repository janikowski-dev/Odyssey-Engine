#include "Modules/WorldModule.h"

#include "Messages/AddedEntityMessage.h"
#include "Messaging/MessageBus.h"
#include "ECS/Registry.h"

namespace Source::Modules
{
    void WorldModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.World = MakeUnique<ECS::Registry>();

        Context.World->OnEntityAdded += [&Context](uint32 Index)
        {
            Context.MessageBus->Enqueue(Messages::AddedEntityMessage { Index });
        };
    }
}