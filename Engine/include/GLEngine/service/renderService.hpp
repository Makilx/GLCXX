#pragma once

#include <GLECore/enum/render.hpp>
#include <GLEInterface/rendering/IRenderer.hpp>
#include <GLEngine/service/service.hpp>

namespace gle {
    class RenderService : public Service {
      public:
        RenderService(DataModel *dataModel, RenderAPI targetAPI) : Service(dataModel), api(targetAPI) {}

      public:
        std::string ToString() const override { return "RenderService"; }

      public:
        RenderMode GetRenderMode() const { return mode; }
        RenderAPI GetRenderAPI() const { return api; }

      public:
        void SetRenderMode(RenderMode mode) { this->mode = mode; }

      protected:
        void OnInit() override;
        void OnUpdate(double deltaTime) override;
        void OnTerminate() override;

      private:
        backend::IRenderer *worldRenderer;
        RenderMode mode = RenderMode::Default;
        RenderAPI api = RenderAPI::OpenGL;
    };
} // namespace gle