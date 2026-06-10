#pragma once

#include <memory>
#include <chrono>
#include <cstdint>
#include <nlohmann/json.hpp>

namespace Core
{
    template<typename T> using SharedPtr = std::shared_ptr<T>;
    template<typename T> using UniquePtr = std::unique_ptr<T>;
    template<typename T> using WeakPtr = std::weak_ptr<T>;

    template<typename T, typename... Args>
    SharedPtr<T> MakeShared(Args&&... InArgs) { return std::make_shared<T>(std::forward<Args>(InArgs)...); }

    template<typename T, typename... Args>
    UniquePtr<T> MakeUnique(Args&&... InArgs) { return std::make_unique<T>(std::forward<Args>(InArgs)...); }

    using uint8 = std::uint8_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;

    using Json = nlohmann::json;

    using Duration = std::chrono::duration<float>;
    using Clock = std::chrono::steady_clock;
}