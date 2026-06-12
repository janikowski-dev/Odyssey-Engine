#pragma once

#include <type_traits>
#include <utility>
#include <memory>
#include <chrono>
#include <cstdint>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

// Namespace needs to be named like that, so the other classes can use these types easily
namespace Source
{
    // Pointers
    template<typename T> using SharedPtr = std::shared_ptr<T>;
    template<typename T> using UniquePtr = std::unique_ptr<T>;
    template<typename T> using WeakPtr = std::weak_ptr<T>;

    template<typename T, typename... Args>
    SharedPtr<T> MakeShared(Args&&... InArgs) { return std::make_shared<T>(std::forward<Args>(InArgs)...); }

    template<typename T, typename... Args>
    UniquePtr<T> MakeUnique(Args&&... InArgs) { return std::make_unique<T>(std::forward<Args>(InArgs)...); }

    // Numbers
    using uint8 = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;

    // Json
    using Json = nlohmann::json;

    // Logs
    inline std::ostream& Debug = std::cout;

    // Time
    using Duration = std::chrono::duration<float>;
    using Clock = std::chrono::steady_clock;
    using Time = std::chrono::steady_clock::time_point;
    
    // Is Empty
    template<typename T, typename = void>
    struct is_empty_type : std::false_type
    {
    };
    
    template<typename T>
    struct is_empty_type<T, std::void_t<>> : std::bool_constant<std::is_empty_v<T>>
    {
    };
    
    template<typename T>
    inline constexpr bool IsEmpty = is_empty_type<T>::value;

    // Is Consumable
    template<typename, typename = void>
    struct is_consumable : std::false_type
    {
    };

    template<typename T>
    struct is_consumable<T, std::void_t<decltype(std::declval<T&>().Handled = true)>> : std::true_type
    {
    };

    template<typename T>
    inline constexpr bool IsConsumable = is_consumable<T>::value;
}

// Namespace has to be like this so the json serializer sees these methods
namespace glm
{
    inline void to_json(Source::Json& J, const glm::vec3& V)
    {
        J = Source::Json::array({ V.x, V.y, V.z });
    }

    inline void from_json(const Source::Json& J, glm::vec3& V)
    {
        V.x = J.at(0).get<float>();
        V.y = J.at(1).get<float>();
        V.z = J.at(2).get<float>();
    }
}