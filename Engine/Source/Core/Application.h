#pragma once

#include "Core/ApplicationConfig.h"
#include "Core/IModuleRegistrar.h"
#include "Core/Context.h"
#include "Core/Minimal.h"

namespace Source::Core
{
	class Application : public IModuleRegistrar
	{
	public:
		Application(const ApplicationConfig& InConfig = ApplicationConfig());

		void Run();

		virtual void RegisterModule(UniquePtr<IModule> Module) override;

	private:
		void CreateInternalModules(const ApplicationConfig& InConfig);
		void InitAllModules(const ApplicationConfig& InConfig);

	private:
		std::vector<UniquePtr<IModule>> Modules;
		Context Context;
	};
}
