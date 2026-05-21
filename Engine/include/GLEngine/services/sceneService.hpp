#pragma once

#include <GLEngine/instance/workspace.hpp>
#include <GLEngine/services/service.hpp>

namespace gle {
    class SceneService : public Service {
      public:
        using Service::Service;

        Workspace *GetActiveWorkspace() const { return activeWorkspace; }
        void SetActiveWorkspace(Workspace *workspace) { activeWorkspace = workspace; }

      protected:
        void OnInit() override {}
        void OnUpdate(double deltaTime) override {}
        void OnTerminate() override { SetActiveWorkspace(NULL); }

      private:
        Workspace *activeWorkspace = NULL;
    };
} // namespace gle