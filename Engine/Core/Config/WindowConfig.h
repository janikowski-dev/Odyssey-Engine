#pragma once

#include <string>
#include <functional>

namespace Core::Config
{
	struct WindowConfig
	{
		uint32_t Width = 1280;
		uint32_t Height = 720;
		bool IsResizeable = true;
		bool UseVSync = true;
		bool RenderWindow = true;
	};
}