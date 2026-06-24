#pragma once

#include "Core/ApplicationConfig.h"
#include "Core/Context.h"

namespace Source::Core
{
	enum class TickPolicy
	{
		Never,
		Always,
		Playtime
	};

	class IModule
	{
	public:
		virtual ~IModule() = default;

		virtual TickPolicy GetTickPolicy() const { return TickPolicy::Never; }

        virtual void Init(const ApplicationConfig Config, Context& Context) {}
		
		virtual void OnBeginPlay(const Context& Context) {}
		virtual void OnEndPlay(const Context& Context) {}

		virtual void Tick(const Context& Context) {}
	};
}
