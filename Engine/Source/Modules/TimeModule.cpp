#include "Modules/TimeModule.h"

namespace Source::Modules
{
    void TimeModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
	    Context.Time = MakeUnique<Core::Time>();
    }
    
    void TimeModule::OnBeginPlay(const Core::Context &Context)
    {
        LastTime = Clock::now();
    }

    void TimeModule::OnEndPlay(const Core::Context &Context)
    {
        Context.Time->DeltaTime = 0.0f;
    }

    void TimeModule::Tick(const Core::Context& Context)
    {
        Time Now = Clock::now();
        Context.Time->DeltaTime = Duration(Now - LastTime).count();
        LastTime = Now;
    }
}
