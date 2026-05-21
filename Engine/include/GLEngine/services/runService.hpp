#pragma once

#include <GLEngine/services/service.hpp>
#include <functional>

namespace gle {
    using RunCallbackFunction = std::function<void(const double deltaTime)>;

    struct RunCallback {
      public:
        std::string name;
        unsigned int priority;
        RunCallbackFunction callback;
    };

    enum class RunPriority : unsigned int {
        Input = 1000,
        Physics = 3000,
        Render = 4000,
        First = 0000,
        Last = 4000,
        Update = 2000,
    };

    class RunService : public Service {
      public:
        std::string ToString() const override { return "RunService"; }
        using Service::Service;

        double GetTime() const;
        double GetDeltaTimeRaw() const;
        double GetDeltaTime() const;
        float GetUpdateSpeed() const;
        void SetUpdateSpeed(float speed);
        double GetFramerate() const;

        void BindToUpdate(std::string bind, unsigned int priority, RunCallbackFunction callback);
        template <typename T>
        void BindToUpdate(std::string bind, unsigned int priority, T *instance,
                          void (T::*method)(const double deltaTime));
        void SetBindPriority(std::string bind, unsigned int priority);
        void UnbindFromUpdate(std::string bind);

      protected:
        void OnUpdate(double deltaTime) override;

      private:
        std::vector<RunCallback> callbacks;
        double time = 0;
        double deltaTime = 0;
        double rawDeltaTime = 0;
        float updateSpeed = 1;
        bool needsSort = false;
        double fps = 0.0;
        double fpsAccumulator = 0.0;
        int fpsFrameCount = 0;
        double fpsUpdateTimer = 0.0;

      private:
        void SortCallbacks();
    };
} // namespace gle