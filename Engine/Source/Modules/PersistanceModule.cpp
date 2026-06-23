#include "Modules/PersistanceModule.h"

#include "Serialization.generated.h"

namespace Source::Modules
{
    void PersistanceModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Serialization::Init(*Context.World);
    }
}