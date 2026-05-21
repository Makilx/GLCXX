#pragma once

#include <GLECore/math/matrix4.hpp>
#include <GLECore/math/size2D.hpp>
#include <GLECore/pch.hpp>
#include <GLEInterface/components/IMaterial.hpp>
#include <GLEInterface/components/IMesh.hpp>
#include <GLEInterface/components/ITexture.hpp>

namespace gle::backend {
    struct RenderObject {
        IMesh *mesh;
        IMaterial *material;
        Mat4 modelMatrix;
    };

    class IRenderer {
      public:
      private:
    };
} // namespace gle::backend