#pragma once

#if defined(REFLECTION_CODEGEN)
    #define COMPONENT      __attribute__((annotate("component")))
    #define PROPERTY(...)  __attribute__((annotate("property:" #__VA_ARGS__)))
#else
    #define COMPONENT
    #define PROPERTY(...)
#endif
