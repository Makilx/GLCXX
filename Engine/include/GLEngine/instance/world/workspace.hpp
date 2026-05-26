#pragma once

#include <GLEngine/instance/instance.hpp>

namespace gle {
    class SceneService;
    class Workspace : public Instance {
      public:
        Workspace() : Instance("Workspace") {
            canBeDestroyed = false;
            canBeMoved = false;
            canBeRenamed = false;
        }

      public:
        std::string GetClassName() const override { return "Workspace"; }

      protected:
        void Register() override {}

      private:
        friend class SceneService;
    };
} // namespace gle