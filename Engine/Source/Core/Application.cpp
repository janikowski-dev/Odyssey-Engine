#include "Application.h"

#include "Modules/EditorModule.h"
#include "Modules/MessagingModule.h"
#include "Modules/PlatformModule.h"
#include "Modules/RenderingModule.h"
#include "Modules/ResourcesModule.h"
#include "Modules/RuntimeModule.h"
#include "Modules/PersistanceModule.h"
#include "Modules/WorldModule.h"

#include "Modules.generated.h"

namespace Source::Core
{
	Application::Application(const ApplicationConfig& InConfig) 
	{
        CreateInternalModules(InConfig);
        CreateExternalModules(this);
        InitInternalModules(InConfig);
	}

	void Application::Run()
	{
    	while (!Context.Window->ShouldClose())
    	{
            for (auto& Module : InternalModules)
            {
                Module->Tick(Context);
            }

            for (auto& Module : ExternalModules)
            {
                Module->Tick(Context);
            }
    	}
	}

    void Application::RegisterModule(UniquePtr<IModule> Module)
    {
        ExternalModules.push_back(std::move(Module));
    }

    void Application::CreateInternalModules(const ApplicationConfig& InConfig)
	{
        InternalModules.push_back(MakeUnique<Modules::WorldModule>());
        InternalModules.push_back(MakeUnique<Modules::RuntimeModule>());
        InternalModules.push_back(MakeUnique<Modules::MessagingModule>());
        InternalModules.push_back(MakeUnique<Modules::RenderingModule>());
        InternalModules.push_back(MakeUnique<Modules::PersistanceModule>());
        InternalModules.push_back(MakeUnique<Modules::PlatformModule>());
        InternalModules.push_back(MakeUnique<Modules::ResourcesModule>());

        if (InConfig.LaunchType == LaunchType::Editor)
        {
            InternalModules.push_back(MakeUnique<Modules::EditorModule>());
        }
	}

    void Application::InitInternalModules(const ApplicationConfig& InConfig)
    {
		for (auto& Module : InternalModules)
        {
            Module->Init(InConfig, Context);
        }
        
        // Temporary
		for (auto& Module : ExternalModules)
        {
            Module->Init(InConfig, Context);
        }
    }
}
