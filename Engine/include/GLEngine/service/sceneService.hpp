#pragma once

#include <GLEngine/instance/world/workspace.hpp>
#include <GLEngine/service/service.hpp>

namespace gle {
    class SceneService : public Service {
      public:
        using Service::Service;

      public:
        Workspace *GetCurrentWorkspace() const { return activeWorkspace; }
        void SetCurrentWorkspace(Workspace *workspace) {
            if (activeWorkspace) {
                workspace->OnUnload();
                delete activeWorkspace;
            }
            activeWorkspace = workspace;
            workspace->OnLoad();
        }
        void CreateBlankWorkspace() { SetCurrentWorkspace(new Workspace()); }

      protected:
        void OnTerminate() override { SetCurrentWorkspace(NULL); }

      private:
        Workspace *activeWorkspace = NULL;
    };
} // namespace gle