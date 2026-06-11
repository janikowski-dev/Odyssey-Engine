#pragma once

#include "ApplicationConfig.h"
#include "Context.h"
#include "IModule.h"
#include "Minimal.h"

namespace Source::Core
{
	class Application
	{
	public:
		Application(const ApplicationConfig& InConfig = ApplicationConfig());

		void Run();

	private:
		std::vector<UniquePtr<IModule>> Modules;
		Context Context;
	};
}
