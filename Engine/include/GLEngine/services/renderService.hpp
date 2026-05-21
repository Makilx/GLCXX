#pragma once

#include <GLEngine/services/service.hpp>

namespace gle {
    class RenderService : public Service {
      public:
        std::string ToString() const override { return "RenderService"; }
        using Service::Service;

      protected:
        void OnInit() override {}
        void OnUpdate(double deltaTime) override {}
        void OnTerminate() override {}

      private:
    };
} // namespace gle