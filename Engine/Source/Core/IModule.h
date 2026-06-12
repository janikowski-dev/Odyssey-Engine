#pragma once

#include "Core/ApplicationConfig.h"
#include "Core/Context.h"

namespace Source::Core
{
	class IModule
	{
	public:
		virtual ~IModule() = default;

        virtual void Init(const ApplicationConfig Config, Context& Context) {}
		virtual void Tick(const Context& Context) {}
	};
}
