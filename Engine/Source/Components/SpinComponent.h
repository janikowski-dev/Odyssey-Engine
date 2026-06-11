#pragma once

#include "../Core/Types.h"

namespace Source::Components
{
    struct SpinComponent
    {
        glm::vec3 Speed { 0.0f };
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SpinComponent, Speed)
}