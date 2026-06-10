#pragma once

#include "../Core/Types.h"

#include <glm/glm.hpp>

namespace Source::Components
{
    struct Spin
    {
        glm::vec3 Speed { 0.0f };
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Spin, Speed)
}