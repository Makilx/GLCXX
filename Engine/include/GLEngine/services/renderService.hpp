#pragma once

#include <GLECore/pch.hpp>
#include <GLEInterface/IRenderer.hpp>
#include <GLEngine/instance/instance.hpp>
#include <GLEngine/services/service.hpp>

namespace gle {
    class RenderService : public Service {
      public:
        std::string ToString() const override { return "RenderService"; }
        using Service::Service;

      protected:
        void OnInit() override;
        void OnUpdate(double deltaTime) override;
        void OnTerminate() override;

      private:
        std::unique_ptr<backend::IRenderer> worldRenderer;
    };
} // namespace gle