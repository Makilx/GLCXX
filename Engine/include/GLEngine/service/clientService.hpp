#pragma once

#include <GLEngine/data/client/window.hpp>
#include <GLEngine/service/service.hpp>

namespace gle {
    class ClientService : public Service {
      public:
        ClientService(DataModel *dataModel, WindowAPI api) : Service(dataModel), currentWindowController(api) {}

      public:
        WindowController &GetController() const;

      private:
        WindowController currentWindowController;
    };
} // namespace gle