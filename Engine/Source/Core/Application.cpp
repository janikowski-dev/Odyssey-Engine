#include "Application.h"

#include "Modules/EditorModule.h"
#include "Modules/MessagingModule.h"
#include "Modules/PlatformModule.h"
#include "Modules/SystemsModule.h"
#include "Modules/ResourcesModule.h"

#include <Windows.h>

namespace Source::Core
{
	Application::Application(const ApplicationConfig& InConfig) 
	{
        CreateInternalModules(InConfig);
        CreateExternalModules(InConfig);
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

	void Application::CreateExternalModules(const ApplicationConfig& InConfig)
	{
        using CreateGameModulesFn = std::vector<UniquePtr<IModule>>(*)();

        std::vector<UniquePtr<IModule>> ExternalModules;

            HMODULE Dll = LoadLibraryA("Game.dll");

            if (!Dll)
            {
                return;
            }

            auto CreateModulesFunction = reinterpret_cast<CreateGameModulesFn>(GetProcAddress(Dll, "CreateGameModules"));

            if (CreateModulesFunction)
            {
                ExternalModules = CreateModulesFunction();

                for (auto& Module : ExternalModules)
                {
                    Modules.push_back(std::move(Module));
                }
            }
            else
            {
                FreeLibrary(Dll);
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
