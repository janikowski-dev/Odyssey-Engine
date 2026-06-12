#pragma once

#include "Core/IModule.h"
#include "Core/Minimal.h"

namespace Source::Editor { class Bridge; }

namespace Source::Modules
{
    class SerializationModule final : public Core::IModule
    {
    public:
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;

    private:
        void Attach(Editor::Bridge& Bridge);
    };
}