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
		Context = MakeUnique<Core::Context>();
		
		Context->World = MakeUnique<ECS::Registry>();

        Modules.push_back(MakeUnique<SerializationModule>());
        Modules.push_back(MakeUnique<MessagingModule>());
        Modules.push_back(MakeUnique<EditorModule>());
        Modules.push_back(MakeUnique<PlatformModule>());
        Modules.push_back(MakeUnique<SystemsModule>());

		for (auto& Module : Modules)
        {
            Module->Init(InConfig, *Context);
        }
	}

	void Application::Run()
	{
    	while (true)
    	{
            for (auto& Module : Modules)
            {
                Module->Tick(*Context);
            }
    	}
	}
}
