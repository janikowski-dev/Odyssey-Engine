#pragma once

#include <type_traits>
#include <utility>
#include <memory>
#include <chrono>
#include <cstdint>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <optional>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <atomic>
#include <mutex>
#include <deque>
#include <unordered_set>
#include <queue>
#include <thread>
#include <fstream>

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
inline std::ostream& DebugLog = std::cout;
inline std::ostream& DebugError = std::cout;

// Time
using Duration = std::chrono::duration<float>;
using Clock = std::chrono::steady_clock;
using Time = std::chrono::steady_clock::time_point;

// Maths
using Vector2 = glm::vec2;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;

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

// Is Arithmetic
template<typename, typename = void>
struct is_arithmetic : std::false_type {};

template<typename T>
struct is_arithmetic<T, std::enable_if_t<std::is_arithmetic_v<T>>> : std::true_type {};

template<typename T>
inline constexpr bool IsArithmetic = is_arithmetic<T>::value;

template<typename... TArgs>
class Event
{
public:
    using Handler = std::function<void(TArgs...)>;

    Event& operator+=(Handler InHandler)
    {
        Handlers.push_back(std::move(InHandler));
        return *this;
    }
    
    void operator()(TArgs... Args) const
    {
        for (const Handler& H : Handlers)
        {
            H(Args...);
        }
    }

private:
    std::vector<Handler> Handlers;
};

// Components serialization
#if defined(REFLECTION_CODEGEN)
    #define EXTERNAL_MODULE __attribute__((annotate("external_module")))
    #define COMPONENT      __attribute__((annotate("component")))
    #define PROPERTY(...)  __attribute__((annotate("property:" #__VA_ARGS__)))
#else
    #define EXTERNAL_MODULE
    #define COMPONENT
    #define PROPERTY(...)
#endif
