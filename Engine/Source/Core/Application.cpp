#include "Application.h"

#include "Modules/EditorModule.h"
#include "Modules/PlatformModule.h"
#include "Modules/RenderingModule.h"
#include "Modules/ResourcesModule.h"
#include "Modules/RuntimeModule.h"
#include "Modules/TimeModule.h"
#include "Modules/SerializationModule.h"
#include "Modules/WorldModule.h"

#include "Modules.generated.h"

namespace Source::Core
{
	Application::Application(const ApplicationConfig& InConfig) : Config(InConfig)
	{
        CreateInternalModules(InConfig);
        CreateExternalModules(this);
        InitAllModules(InConfig);
	}

	void Application::Run()
	{
        if (Config.LaunchType == LaunchType::Game)
        {
            Context.Runtime->ShouldBePlaying = true;
        }

    	while (!Context.Window->ShouldClose())
    	{
            if (Context.Runtime->BeganPlaying)
            {
                for (auto& Module : Modules)
                {
                    Module->OnBeginPlay(Context);
                }
            }
            else if (Context.Runtime->EndedPlaying)
            {
                for (auto& Module : Modules)
                {
                    Module->OnEndPlay(Context);
                }
            }

            for (auto& Module : Modules)
            {
                if (Module->GetTickPolicy() == TickPolicy::Never || (Module->GetTickPolicy() == TickPolicy::Playtime && !Context.Runtime->IsPlaying))
                {
                    continue;
                }

                Module->Tick(Context);
            }
    	}
	}

    void Application::RegisterModule(UniquePtr<IModule> Module)
    {
        Modules.push_back(std::move(Module));
    }

    void Application::CreateInternalModules(const ApplicationConfig& InConfig)
	{
        Modules.push_back(MakeUnique<Modules::WorldModule>());
        Modules.push_back(MakeUnique<Modules::SerializationModule>());
        Modules.push_back(MakeUnique<Modules::TimeModule>());
        Modules.push_back(MakeUnique<Modules::RuntimeModule>());
        Modules.push_back(MakeUnique<Modules::PlatformModule>());
        Modules.push_back(MakeUnique<Modules::ResourcesModule>());
        Modules.push_back(MakeUnique<Modules::RenderingModule>());

        if (InConfig.LaunchType == LaunchType::Editor)
        {
            Modules.push_back(MakeUnique<Modules::EditorModule>());
        }
	}

    void Application::InitAllModules(const ApplicationConfig& InConfig)
    {
		for (auto& Module : Modules)
        {
            Module->Init(InConfig, Context);
        }
    }
}
