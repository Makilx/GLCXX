#pragma once

#include <GLEngine/service/service.hpp>
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
        using RunServiceCallback = std::function<void(const double)>;
        struct UpdateBind {
            int priority;
            std::string name;
            RunServiceCallback callback;
        };

      public:
        double GetTime() const { return time; }
        double GetDeltaTime() const { return deltaTime; }
        int GetFramerate() const;

        void BindToUpdate(std::string bind, RunServiceCallback callback,
                          int priority = static_cast<int>(RunPriority::Last));
        template <typename T>
        void BindToUpdate(std::string bind, T *instance, void (T::*method)(const double),
                          int priority = static_cast<int>(RunPriority::Last));
        void UnbindFromUpdate(std::string bind) { binds.erase(std::find(bind.begin(), bind.end(), bind)); }
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
                    break;
                }
            }
        }

      protected:
        void OnInit() override;
        void OnUpdate(double deltaTime) override;
        void OnTerminate() override;

      private:
        std::vector<UpdateBind> binds;
        double time = 0;
        double deltaTime = 0;
    };
} // namespace gle