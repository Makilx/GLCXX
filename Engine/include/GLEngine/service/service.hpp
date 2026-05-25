#pragma once

#include <GLECore/pch.hpp>

namespace gle {
    class DataModel;
    class Service {
      public:
        Service(DataModel *dataModel) : dataModel(dataModel) {}
        virtual ~Service() = default;

      public:
        virtual std::string ToString() const { return "Service"; }
        DataModel *GetDataModel() const { return dataModel; }

      protected:
        virtual void OnInit() {}
        virtual void OnUpdate(double deltaTime) {}
        virtual void OnTerminate() {}

      private:
        DataModel *dataModel;

      private:
        friend class DataModel;
    };
} // namespace gle