#include "Modules/WorkspaceModule.h"

namespace Source::Modules
{
    void WorkspaceModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
	    Context.Workspace = MakeUnique<Core::Workspace>();
    }
}
