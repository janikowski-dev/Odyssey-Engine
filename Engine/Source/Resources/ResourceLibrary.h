#pragma once

#include "Core/Minimal.h"

namespace Source::Resources
{
    template<typename TResource>
    class ResourceLibrary
    {
    public:
        using LoadFunction = std::function<std::optional<TResource>(const std::filesystem::path&)>;

        explicit ResourceLibrary(LoadFunction InLoad);

        std::size_t Refresh(const std::string& Path);

        void SetExtensions(std::vector<std::string> InExtensions);

        TResource* Add(const std::string& InId, TResource&& InResource);
        TResource* Get(const std::string& InId) const;
        bool Has(const std::string& InId) const;
        void Remove(const std::string& InId);
        void Clear();
        std::size_t Count() const;

    private:
        bool Accepts(const std::filesystem::path& File) const;
        std::string MakeId(const std::filesystem::path& Root, const std::filesystem::path& File) const;

        std::unordered_map<std::string, UniquePtr<TResource>> Resources;
        std::vector<std::string> Extensions;
        LoadFunction Load;
    };
}

#include "ResourceLibrary.inl"