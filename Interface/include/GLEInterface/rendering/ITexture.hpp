#pragma once

#include <GLECore/enum/texture.hpp>
#include <GLECore/math/size2D.hpp>
#include <GLECore/pch.hpp>

namespace gle::backend {
    class ITexture {
      public:
        virtual ~ITexture() = default;
        virtual bool LoadFromFile(const std::string &filePath) = 0;
        virtual bool LoadFromMemory(const void *data, Size2D size, TextureFormat format) = 0;
        virtual void Unload() = 0;

      public:
        virtual bool IsLoaded() const = 0;
        virtual Size2D GetSize() const = 0;
        virtual TextureFormat GetFormat() const = 0;

      public:
        virtual void Use(std::uint32_t slot = 0) = 0;
    };
} // namespace gle::backend