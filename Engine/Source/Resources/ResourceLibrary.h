#pragma once

#include "../Core/Types.h"

#include <string>
#include <unordered_map>

namespace Source::Resources
{
    template<typename T>
    class ResourceLibrary
    {
    public:
        T* Add(const std::string& InId, T&& InResource);
        T* Get(const std::string& InId) const;
        bool Has(const std::string& InId) const;
        void Remove(const std::string& InId);
        void Clear();
        std::size_t Count() const;

    private:
        std::unordered_map<std::string, UniquePtr<T>> Resources;
    };
}

#include "ResourceLibrary.inl"