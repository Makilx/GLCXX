#pragma once

#include <GLEInterface/rendering/IMesh.hpp>
#include <GLEInterface/rendering/Material.hpp>
#include <GLEInterface/window/IWindow.hpp>

namespace gle::backend {
    struct RenderObject {
      public:
        const IMesh *mesh;
        const Material *material;
        const Mat4 modelMatrix;
        int renderPriority;
    };

    struct IRenderer {
      public:
        virtual ~IRenderer() = default;
        virtual void Init(IWindow *window) = 0;
        virtual void Terminate() = 0;

      public:
        virtual IShader *GetDefaultShader() const = 0;

      public:
        virtual void BeginFrame() = 0;
        virtual void Flush() = 0;
        virtual void Submit(const RenderObject &object) = 0;
        virtual void EndFrame() = 0;
        virtual void SetBackgroundColor(Color bgColor) = 0;
        virtual void SetDefaultShader(IShader *defaultShader) = 0;

      public:
        struct RenderBatch {
          public:
            const IMesh *mesh;
            const Material *material;
            const std::vector<Mat4> modelMatrices;
            int renderPriority;
        };

      protected:
        IWindow *GetWindow() const { return userWindow; }

      private:
        IWindow *userWindow = NULL;
    };
} // namespace gle::backend