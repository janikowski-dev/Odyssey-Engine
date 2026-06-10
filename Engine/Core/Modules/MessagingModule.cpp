#include "MessagingModule.h"

namespace Core::Modules
{
    void MessagingModule::Init(const ApplicationConfig Config, Context& Context)
    {
	    Context.MessageBus = MakeUnique<Messaging::MessageBus>();
    }

    void MessagingModule::Tick(const Context& Context)
    {
	    Context.MessageBus->Flush();
    }
}