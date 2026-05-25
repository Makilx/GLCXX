#pragma once

#include <GLECore/math/color.hpp>
#include <GLECore/pch.hpp>
#include <GLEInterface/rendering/IShader.hpp>
#include <GLEInterface/rendering/ITexture.hpp>

namespace gle {
    struct Material {
      public:
        backend::ITexture *baseTexture = NULL;
        Color baseColor = Color::White;
        backend::IShader *targetShader = NULL;
    };
} // namespace gle