#pragma once

#include <GLECore/pch.hpp>

namespace gle {
    class DataModel;

    class Service {
      public:
        virtual std::string ToString() const { return "Service"; }
        Service(DataModel *dataModel) : dataModel(dataModel) {}

        DataModel *GetDataModel() const { return dataModel; }
        template <typename T>
        T *As() const {
            return dynamic_cast<T *>(this);
        }

      protected:
        virtual void OnInit() {}
        virtual void OnUpdate(double deltaTime) {}
        virtual void OnTerminate() {}

      private:
        DataModel *dataModel;

        friend class DataModel;
    };
} // namespace gle
