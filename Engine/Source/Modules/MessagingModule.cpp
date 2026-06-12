#include "Modules/MessagingModule.h"

namespace Source::Modules
{
    void MessagingModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
	    Context.MessageBus = MakeUnique<Messaging::MessageBus>();
    }

    void MessagingModule::Tick(const Core::Context& Context)
    {
	    Context.MessageBus->Flush();
    }
}