#pragma once

#include "Resources/ResourceLibrary.h"

namespace Source::Resources
{
    template<typename T>
    T* ResourceLibrary<T>::Add(const std::string& InId, T&& InResource)
    {
        auto Result = Resources.insert_or_assign(InId, MakeUnique<T>(std::move(InResource)));
        return Result.first->second.get();
    }

    template<typename T>
    T* ResourceLibrary<T>::Get(const std::string& InId) const
    {
        auto It = Resources.find(InId);

        if (It != Resources.end())
        {
            return It->second.get();
        }

        return nullptr;
    }

    template<typename T>
    bool ResourceLibrary<T>::Has(const std::string& InId) const
    {
        return Resources.find(InId) != Resources.end();
    }

    template<typename T>
    void ResourceLibrary<T>::Remove(const std::string& InId)
    {
        Resources.erase(InId);
    }

    template<typename T>
    void ResourceLibrary<T>::Clear()
    {
        Resources.clear();
    }

    template<typename T>
    std::size_t ResourceLibrary<T>::Count() const
    {
        return Resources.size();
    }
}