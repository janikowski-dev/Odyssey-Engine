#pragma once

#include "Resources/ResourceLibrary.h"

namespace Source::Resources
{
    template<typename TResource>
    TResource* ResourceLibrary<TResource>::Add(const std::string& InId, TResource&& InResource)
    {
        auto Result = Resources.insert_or_assign(InId, MakeUnique<TResource>(std::move(InResource)));
        return Result.first->second.get();
    }

    template<typename TResource>
    TResource* ResourceLibrary<TResource>::Get(const std::string& InId) const
    {
        auto It = Resources.find(InId);

        if (It != Resources.end())
        {
            return It->second.get();
        }

        return nullptr;
    }

    template<typename TResource>
    bool ResourceLibrary<TResource>::Has(const std::string& InId) const
    {
        return Resources.find(InId) != Resources.end();
    }

    template<typename TResource>
    void ResourceLibrary<TResource>::Remove(const std::string& InId)
    {
        Resources.erase(InId);
    }

    template<typename TResource>
    void ResourceLibrary<TResource>::Clear()
    {
        Resources.clear();
    }

    template<typename TResource>
    std::size_t ResourceLibrary<TResource>::Count() const
    {
        return Resources.size();
    }
}