#pragma once

#include <GLECore/math/size2D.hpp>
#include <GLECore/pch.hpp>

namespace gle::backend {

    enum class TextureType {
        RGB = 0,
        RGBA = 1
    };

    class ITexture {
      public:
        virtual ~ITexture() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void Use(unsigned int slot = 0) const = 0;

        virtual Size2D GetSize() const = 0;
        virtual TextureType GetType() const = 0;
    };

} // namespace gle::backend