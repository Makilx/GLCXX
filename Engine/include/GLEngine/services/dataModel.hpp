#pragma once

#include <GLECore/pch.hpp>

#include <GLEngine/services/renderService.hpp>
#include <GLEngine/services/runService.hpp>
#include <GLEngine/services/sceneService.hpp>
#include <GLEngine/services/service.hpp>

namespace gle {
    class DataModel;
    class RunService;

    class DataModel {
      public:
        std::string ToString() const { return "Game"; }

        Service *GetService(std::string service) { return services[service]; }
        template <typename T>
        T *GetService() {
            for (auto &[name, s] : services) {
                T *tr = s->As<T>();
                if (tr)
                    return tr;
            }
        }

      public:
        void Init() {
            if (initialized)
                return;

            // Create all services
            RegisterService<RenderService>();
            RegisterService<RunService>();
            RegisterService<SceneService>();

            // Load all services
            for (auto &[name, service] : services) {
                service->OnInit();
            }
        }
        void Terminate() {
            if (!initialized)
                return;

            // Terminate all services
            // Delete all services
            for (auto &[name, service] : services) {
                service->OnTerminate();
                delete service;
            }
            services.clear();
            initialized = false;
        }

      private:
        std::unordered_map<std::string, Service *> services;
        bool initialized = false;

      private:
        template <typename T>
        void RegisterService() {
            T *service = new T(this);
            services.insert({service->ToString(), service});
        }

        void Update(double deltaTime) {
            for (auto &[name, s] : services) {
                s->OnUpdate(deltaTime);
            }
        }

        friend class RunService;
    };
} // namespace gle