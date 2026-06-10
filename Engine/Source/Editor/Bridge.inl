#pragma once

#include "Bridge.h"

#include "../Core/Types.h"

namespace Source::Editor
{
    template<typename TIn, typename TOut, typename Fn>
    void Bridge::On(std::string_view Method, Fn&& Function)
    {
        Handlers[std::string(Method)] = [Fn = std::forward<Fn>(Function)](const Json& Params) -> Json
        {
            TIn Input{};

            if constexpr (!IsEmpty<TIn>)
            {
                Input = Params.get<TIn>();
            }

            if constexpr (IsEmpty<TOut>)
            {
                Fn(Input);
                return Json::object();
            }
            else
            {
                TOut Output = Fn(Input);
                return Json(Output);
            }
        };
    }
}
