#pragma once

#include <GLECore/math/matrix4.hpp>
#include <GLECore/math/size2D.hpp>
#include <GLECore/pch.hpp>
#include <GLEInterface/components/IMaterial.hpp>
#include <GLEInterface/components/IMesh.hpp>
#include <GLEInterface/components/ITexture.hpp>

namespace gle::backend {
    struct RenderObject {
        const IMesh *mesh;
        const IMaterial *material;
        Mat4 modelMatrix;
        int renderLayer;
    };

    class IRenderer {
      public:
        virtual ~IRenderer() = default;

        virtual void Init() = 0;
        virtual void Terminate() = 0;

        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;

        virtual void Submit(const RenderObject &object) = 0;
        virtual void Flush() = 0;
    };

} // namespace gle::backend