#pragma once

#include "Core/Minimal.h"

namespace Source::Resources
{
    template<typename TResource>
    class ResourceLibrary
    {
    public:
        TResource* Add(const std::string& InId, TResource&& InResource);
        TResource* Get(const std::string& InId) const;
        bool Has(const std::string& InId) const;
        void Remove(const std::string& InId);
        void Clear();
        std::size_t Count() const;

    private:
        std::unordered_map<std::string, UniquePtr<TResource>> Resources;
    };
}

#include "ResourceLibrary.inl"