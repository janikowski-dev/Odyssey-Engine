#include "Application.h"

#include "Modules/EditorModule.h"
#include "Modules/MessagingModule.h"
#include "Modules/PlatformModule.h"
#include "Modules/SerializationModule.h"
#include "Modules/SystemsModule.h"

namespace Core
{
	Application::Application(const ApplicationConfig& InConfig) 
	{
        Modules.push_back(MakeUnique<Modules::SerializationModule>());
        Modules.push_back(MakeUnique<Modules::MessagingModule>());
        Modules.push_back(MakeUnique<Modules::EditorModule>());
        Modules.push_back(MakeUnique<Modules::PlatformModule>());
        Modules.push_back(MakeUnique<Modules::SystemsModule>());

		for (auto& Module : Modules)
        {
            Module->Init(InConfig, Context);
        }
	}

	void Application::Run()
	{
    	while (true)
    	{
            for (auto& Module : Modules)
            {
                Module->Tick(Context);
            }
    	}
	}
}
