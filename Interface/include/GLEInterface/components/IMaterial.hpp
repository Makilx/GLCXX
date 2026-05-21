#pragma once

#include <GLECore/math/color.hpp>
#include <GLECore/pch.hpp>
#include <GLEInterface/components/ITexture.hpp>

namespace gle::backend {
    struct IMaterial {
      public:
        ITexture *baseTexture;
        Color baseColor;
    };
} // namespace gle::backend