#include "Modules/RuntimeModule.h"

namespace Source::Modules
{
    void RuntimeModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
	    Context.Runtime = MakeUnique<Core::Runtime>();
    }

    void RuntimeModule::Tick(const Core::Context &Context)
    {
        Context.Runtime->BeganPlaying = Context.Runtime->ShouldBePlaying && !Context.Runtime->IsPlaying;
        Context.Runtime->EndedPlaying = !Context.Runtime->ShouldBePlaying && Context.Runtime->IsPlaying;
        Context.Runtime->IsPlaying = Context.Runtime->ShouldBePlaying;
    }
}
