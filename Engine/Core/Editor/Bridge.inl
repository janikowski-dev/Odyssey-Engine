#pragma once

#include "Bridge.h"

namespace Core::Editor
{
    template<typename TIn, typename TOut>
    void Bridge::On(const std::string& Method, std::function<TOut(const TIn&)> Fn)
    {
        Handlers[Method] = [Fn = std::move(Fn)](const Json& Params) -> Json
        {
            TIn input{};

            if constexpr (!std::is_empty_v<TIn>)
            {
                input = Params.get<TIn>();
            }

            if constexpr (std::is_empty_v<TOut>)
            {
                Fn(input);
                return Json::object();
            }
            else
            {
                TOut output = Fn(input);

                if constexpr (std::is_empty_v<TOut>)
                {
                    return Json::object();
                }
                else
                {
                    return Json(output);
                }
            }
        };
    }
}
