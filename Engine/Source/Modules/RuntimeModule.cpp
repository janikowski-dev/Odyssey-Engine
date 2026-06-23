#include "Modules/RuntimeModule.h"
#include "RuntimeModule.h"

namespace Source::Modules
{
    void RuntimeModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
	    Context.Runtimer = MakeUnique<Runtime::Runtimer>();
        LastTime = Clock::now();
    }

    void RuntimeModule::Tick(const Core::Context& Context)
    {
        Time Now = Clock::now();
        Context.Runtimer->DeltaTime = Duration(Now - LastTime).count();
        Context.Runtimer->CurrentTime = Now;
        LastTime = Now;
    }
}
