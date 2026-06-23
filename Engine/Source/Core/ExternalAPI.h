#pragma once

#include "Core/IModuleRegistrar.h"

#if defined(_WIN32)
  #define ODYSSEY_EXPORT __declspec(dllexport)
#endif

extern "C"
{
    typedef void (*RegisterGameModulesFn)(Source::Core::IModuleRegistrar* registrar);
}