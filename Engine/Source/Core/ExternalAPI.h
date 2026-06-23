#pragma once

#include "Core/IModule.h"
#include "Core/Minimal.h"

#if defined(_WIN32)
  #define ODYSSEY_EXPORT __declspec(dllexport)
#endif

extern "C"
{
    typedef std::vector<UniquePtr<Source::Core::IModule>> (*CreateGameModulesFn)();
}