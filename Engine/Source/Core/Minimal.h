#pragma once

#include <type_traits>
#include <utility>
#include <memory>
#include <array>
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
#include <cstdarg>
#include <cstdio> 

// Pointers
template<typename T> using SharedPtr = std::shared_ptr<T>;
template<typename T> using UniquePtr = std::unique_ptr<T>;
template<typename T> using WeakPtr = std::weak_ptr<T>;

template<typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... InArgs) { return std::make_shared<T>(std::forward<Args>(InArgs)...); }
template<typename T, typename... Args>
UniquePtr<T> MakeUnique(Args&&... InArgs) { return std::make_unique<T>(std::forward<Args>(InArgs)...); }

// Unsigned integers
using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

// Integers
using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

// Json
using Json = nlohmann::json;

// Time
using Duration = std::chrono::duration<float>;
using Clock = std::chrono::steady_clock;
using Time = std::chrono::steady_clock::time_point;

// Maths
using Vector2 = glm::vec2;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;
using Matrix4 = glm::mat4;

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

// Logs forwarding
inline std::function<void(const std::string&)>& LogForward()
{
    static std::function<void(const std::string&)> Fn;
    return Fn;
}

inline void LogDispatch(std::ostream& Console, const char* Prefix, const char* Format, va_list Args)
{
    va_list ArgsCopy;
    va_copy(ArgsCopy, Args);
    const int Needed = std::vsnprintf(nullptr, 0, Format, ArgsCopy);
    va_end(ArgsCopy);

    std::string Message;

    if (Needed > 0)
    {
        Message.resize(static_cast<size_t>(Needed));
        std::vsnprintf(Message.data(), Message.size() + 1, Format, Args);
    }

    const std::string Full = std::string(Prefix) + Message;

    Console << Full << std::flush;

    if (LogForward())
    {
        LogForward()(Full);
    }
}

#if defined(__GNUC__) || defined(__clang__)
    #define LOG_PRINTF_CHECK(FmtIdx, ArgIdx) __attribute__((format(printf, FmtIdx, ArgIdx)))
#else
    #define LOG_PRINTF_CHECK(FmtIdx, ArgIdx)
#endif

inline void DebugLog(const char* Format, ...) LOG_PRINTF_CHECK(1, 2);
inline void DebugLog(const char* Format, ...)
{
    va_list Args;
    va_start(Args, Format);
    LogDispatch(std::cout, "[log] ", Format, Args);
    va_end(Args);
}

inline void DebugWarn(const char* Format, ...) LOG_PRINTF_CHECK(1, 2);
inline void DebugWarn(const char* Format, ...)
{
    va_list Args;
    va_start(Args, Format);
    LogDispatch(std::cout, "[warn] ", Format, Args);
    va_end(Args);
}

inline void DebugError(const char* Format, ...) LOG_PRINTF_CHECK(1, 2);
inline void DebugError(const char* Format, ...)
{
    va_list Args;
    va_start(Args, Format);
    LogDispatch(std::cout, "[error] ", Format, Args);
    va_end(Args);
}

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