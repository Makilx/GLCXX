#pragma once

#include <GLECore/enum/render.hpp>
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
        IRenderer(RenderAPI api) : currentAPI(api) {}
        virtual ~IRenderer() { Terminate(); }
        virtual void Init(IWindow *window) { userWindow = window; }
        virtual void Terminate();

      public:
        virtual IShader *GetDefaultShader() const = 0;
        virtual bool IsVSYNCEnabled() const = 0;

        RenderAPI GetAPI() const { return currentAPI; }
        RenderMode GetRenderMode() const { return mode; }

      public:
        virtual void BeginFrame() = 0;
        virtual void Flush() = 0;
        virtual void Submit(const RenderObject &object) = 0;
        virtual void EndFrame() = 0;
        virtual void SetBackgroundColor(Color bgColor) = 0;
        virtual void SetDefaultShader(IShader *defaultShader) = 0;
        virtual void SetVSYNC(bool enabled) = 0;
        void SetRenderMode(RenderMode mode) { this->mode = mode; }

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
        RenderAPI currentAPI;
        RenderMode mode;
    };
} // namespace gle::backend