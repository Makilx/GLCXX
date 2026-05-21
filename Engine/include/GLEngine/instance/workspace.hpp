#pragma once

#include <GLEngine/instance/instance.hpp>

namespace gle {
    class Workspace : public Instance {
      public:
        using Instance::Instance;

      protected:
        void OnLoad() override {}
        void OnUnload() override {}
    };
} // namespace gle