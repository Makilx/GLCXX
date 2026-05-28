#pragma once

#include <GLECore/debug/logger.hpp>
#include <GLECore/pch.hpp>
#include <GLEngine/service/runService.hpp>
#include <GLEngine/service/service.hpp>

namespace gle {
    class RunService;
    class DataModel {
      public:
        void Init() {
            if (initialized)
                return;
            initialized = true;

            Write(LogType::Output, "Initializing data model");

            // Create all services
            RegisterService(new RunService(this));

            // Load all services
            for (auto &[id, service] : services) {
                service->OnInit();
            }
        }
        void Terminate() {
            if (!initialized)
                return;
            initialized = false;

            // Terminate all services and clean them
            for (auto &[id, service] : services) {
                service->OnTerminate();
                delete service;
            }
            services.clear();
        }

      public:
        Service *GetService(std::string s) const {
            for (auto &[id, service] : services) {
                if (id == s)
                    return service;
            }
            return NULL;
        }
        template <typename T>
        T *GetService() const {
            for (auto &[id, service] : services) {
                T *c = dynamic_cast<T *>(service);
                if (c)
                    return c;
            }
            return NULL;
        }

      private:
        std::unordered_map<std::string, Service *> services;
        bool initialized = false;

      private:
        void Update(double deltaTime) {
            for (auto &[id, service] : services) {
                GetService<RunService>()->OnUpdate(deltaTime);
            }
        }
        void RegisterService(Service *service) { services.insert({service->ToString(), service}); }

        friend class RunService;
    };
} // namespace gle