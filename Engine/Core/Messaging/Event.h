#pragma once

#include <type_traits>
#include <utility>

namespace Core::Messaging
{
    struct Event
    {
        bool Handled = false;
    };

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
