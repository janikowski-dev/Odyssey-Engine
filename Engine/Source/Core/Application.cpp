#include "Application.h"

#include "Modules/EditorModule.h"
#include "Modules/MessagingModule.h"
#include "Modules/PlatformModule.h"
#include "Modules/SystemsModule.h"
#include "Modules/ResourcesModule.h"

#include "Modules.generated.h"

namespace Source::Core
{
	Application::Application(const ApplicationConfig& InConfig) 
	{
        CreateInternalModules(InConfig);
        CreateExternalModules(this);
        InitAllModules(InConfig);
	}

	void Application::Run()
	{
    	while (!Context.Window->ShouldClose())
    	{
            for (auto& Module : Modules)
            {
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
        Modules.push_back(MakeUnique<Modules::SystemsModule>());

        if (InConfig.LaunchType == LaunchType::Editor)
        {
            Modules.push_back(MakeUnique<Modules::EditorModule>());
        }

        Modules.push_back(MakeUnique<Modules::MessagingModule>());
        Modules.push_back(MakeUnique<Modules::PlatformModule>());
        Modules.push_back(MakeUnique<Modules::ResourcesModule>());
	}

    void Application::InitAllModules(const ApplicationConfig& InConfig)
    {
		for (auto& Module : Modules)
        {
            Module->Init(InConfig, Context);
        }
    }
}
