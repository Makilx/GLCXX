#pragma once

#include <GLEngine/service/service.hpp>
#include <algorithm>
#include <functional>

namespace gle {
    enum class RunPriority : int {
        First = 0,
        Input = 1000,
        Physics = 2000,
        Camera = 3000,
        Render = 4000,
        Last = 5000,
    };

    class RunService : public Service {
      private:
        using Service::Service;
        using RunServiceCallback = std::function<void(const double)>;
        struct UpdateBind {
            int priority;
            std::string name;
            RunServiceCallback callback;
        };

      public:
        std::string ToString() const override { return "RunService"; }

      public:
        double GetTime() const { return time; }
        double GetDeltaTime() const { return deltaTime; }
        int GetFramerate() const { return 1 / deltaTime; }

        void BindToUpdate(std::string bind, RunServiceCallback callback,
                          int priority = static_cast<int>(RunPriority::Last));
        template <typename T>
        void BindToUpdate(std::string bind, T *instance, void (T::*method)(const double),
                          int priority = static_cast<int>(RunPriority::Last));
        void UnbindFromUpdate(std::string bind);
        bool IsBoundToUpdate(std::string bind) {
            for (UpdateBind &b : binds) {
                if (b.name == bind)
                    return true;
            }
            return false;
        }
        void SetBindPriority(std::string bind, int priority) {
            for (UpdateBind &b : binds) {
                if (b.name == bind) {
                    b.priority = priority;
                    std::sort(binds.begin(), binds.end(),
                              [](const UpdateBind &a, const UpdateBind &b) { return a.priority < b.priority; });
                    break;
                }
            }
        }

      protected:
        void OnUpdate(double deltaTime) override;

      private:
        std::vector<UpdateBind> binds;
        double time = 0;
        double deltaTime = 0;
    };
} // namespace gle