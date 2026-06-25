#pragma once

#include "ResourceLibrary.h"

namespace Source::Resources
{
    template<typename TResource>
    ResourceLibrary<TResource>::ResourceLibrary(LoadFunction InLoad) : Load(std::move(InLoad))
    {
    }

    template<typename TResource>
    void ResourceLibrary<TResource>::SetExtensions(std::vector<std::string> InExtensions)
    {
        Extensions = std::move(InExtensions);
    }

    template<typename TResource>
    bool ResourceLibrary<TResource>::Accepts(const std::filesystem::path& File) const
    {
        if (Extensions.empty())
        {
            return true;
        }

        const std::string Extension = File.extension().string();

        for (const std::string& Allowed : Extensions)
        {
            if (Extension == Allowed)
            {
                return true;
            }
        }

        return false;
    }

    template<typename TResource>
    std::string ResourceLibrary<TResource>::MakeId(const std::filesystem::path& Root, const std::filesystem::path& File) const
    {
        std::filesystem::path Relative = File.lexically_relative(Root);
        Relative.replace_extension("");
        return Relative.generic_string();
    }

    template<typename TResource>
    std::size_t ResourceLibrary<TResource>::Refresh(const std::string& Path)
    {
        const std::filesystem::path Root(Path);

        std::error_code Error;
        if (!std::filesystem::is_directory(Root, Error))
        {
            return 0;
        }

        std::size_t Added = 0;

        std::filesystem::recursive_directory_iterator It(Root, Error), End;
        for (; !Error && It != End; It.increment(Error))
        {
            const std::filesystem::directory_entry& Entry = *It;

            if (!Entry.is_regular_file(Error) || Error || !Accepts(Entry.path()))
            {
                Error.clear();
                continue;
            }

            std::string Id = MakeId(Root, Entry.path());

            if (Has(Id))
            {
                continue;
            }

            std::optional<TResource> Resource = Load(Entry.path());

            if (!Resource)
            {
                continue;
            }

            Add(Id, std::move(*Resource));
            ++Added;
        }

        return Added;
    }
    
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