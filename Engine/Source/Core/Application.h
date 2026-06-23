#pragma once

#include "Core/ApplicationConfig.h"
#include "Core/Context.h"
#include "Core/IModule.h"
#include "Core/Minimal.h"

namespace Source::Core
{
	class Application
	{
	public:
		Application(const ApplicationConfig& InConfig = ApplicationConfig());

		void Run();

	private:
		void CreateInternalModules(const ApplicationConfig& InConfig);
		void CreateExternalModules(const ApplicationConfig& InConfig);
		void InitAllModules(const ApplicationConfig& InConfig);

	private:
		std::vector<UniquePtr<IModule>> Modules;
		Context Context;
	};
}
