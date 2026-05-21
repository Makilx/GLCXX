#include <GLEngine/services/dataModel.hpp>
#include <GLEngine/services/runService.hpp>
#include <algorithm>
#include <utility>

namespace gle {
    double RunService::GetTime() const {
        return time;
    }

    double RunService::GetDeltaTime() const {
        return deltaTime;
    }

    double RunService::GetDeltaTimeRaw() const {
        return rawDeltaTime;
    }

    float RunService::GetUpdateSpeed() const {
        return updateSpeed;
    }

    void RunService::SetUpdateSpeed(float speed) {
        updateSpeed = speed;
    }

    double RunService::GetFramerate() const {
        return fps;
    }

    void RunService::BindToUpdate(std::string bind, unsigned int priority, RunCallbackFunction callback) {
        // overwrite if exists (fast linear replace)
        for (auto &cb : callbacks) {
            if (cb.name == bind) {
                cb.priority = priority;
                cb.callback = std::move(callback);
                needsSort = true;
                return;
            }
        }

        callbacks.push_back(RunCallback{std::move(bind), priority, std::move(callback)});

        needsSort = true;
    }

    template <typename T>
    void RunService::BindToUpdate(std::string bind, unsigned int priority, T *instance,
                                  void (T::*method)(const double deltaTime)) {
        BindToUpdate(std::move(bind), priority, [instance, method](const double dt) { (instance->*method)(dt); });
    }

    void RunService::SetBindPriority(std::string bind, unsigned int priority) {
        for (auto &cb : callbacks) {
            if (cb.name == bind) {
                cb.priority = priority;
                needsSort = true;
                return;
            }
        }
    }

    void RunService::UnbindFromUpdate(std::string bind) {
        auto it =
            std::remove_if(callbacks.begin(), callbacks.end(), [&](const RunCallback &cb) { return cb.name == bind; });

        if (it != callbacks.end()) {
            callbacks.erase(it, callbacks.end());
        }
    }

    void RunService::SortCallbacks() {
        std::sort(callbacks.begin(), callbacks.end(),
                  [](const RunCallback &a, const RunCallback &b) { return a.priority < b.priority; });

        needsSort = false;
    }

    void RunService::OnUpdate(double dt) {
        double scaledDt = dt * updateSpeed;

        deltaTime = scaledDt;
        rawDeltaTime = dt;

        // ---- FPS tracking ----
        fpsAccumulator += scaledDt;
        fpsFrameCount++;
        fpsUpdateTimer += scaledDt;

        if (fpsUpdateTimer >= 1.0) {
            fps = static_cast<double>(fpsFrameCount) / fpsUpdateTimer;
            fpsFrameCount = 0;
            fpsUpdateTimer = 0.0;
        }

        if (needsSort) {
            SortCallbacks();
        }

        // Update services first
        if (GetDataModel())
            GetDataModel()->Update(rawDeltaTime);

        // Update all
        const size_t size = callbacks.size();
        for (size_t i = 0; i < size; ++i) {
            callbacks[i].callback(deltaTime);
        }

        time += scaledDt;
    }

} // namespace gle