#include <GLEngine/service/dataModel.hpp>
#include <GLEngine/service/runService.hpp>

void gle::RunService::BindToUpdate(std::string bind, RunServiceCallback callback, int priority) {
    if (IsBoundToUpdate(bind)) {
        for (UpdateBind &b : binds) {
            if (b.name == bind) {
                b.callback = callback;
                b.priority = priority;
                std::sort(binds.begin(), binds.end(),
                          [](const UpdateBind &a, const UpdateBind &b) { return a.priority < b.priority; });
                return;
            }
        }
    }

    binds.push_back({priority, bind, callback});
    std::sort(binds.begin(), binds.end(),
              [](const UpdateBind &a, const UpdateBind &b) { return a.priority < b.priority; });
}

template <typename T>
void gle::RunService::BindToUpdate(std::string bind, T *instance, void (T::*method)(const double), int priority) {
    BindToUpdate(bind, [=](const double event) { (instance->*method)(event); }, priority);
}

void gle::RunService::UnbindFromUpdate(std::string bind) {
    for (int i = 0; i < binds.size(); i++) {
        if (binds[i].name == bind) {
            binds.erase(binds.begin() + i);
            std::sort(binds.begin(), binds.end(),
                      [](const UpdateBind &a, const UpdateBind &b) { return a.priority < b.priority; });
            return;
        }
    }
}

void gle::RunService::OnUpdate(double deltaTime) {
    this->deltaTime = deltaTime;
    time += deltaTime;

    // Update services first
    for (auto &[id, service] : GetDataModel()->services) {
        if (service != this) {
            service->OnUpdate(deltaTime);
        }
    }

    // Update callbacks
    for (const UpdateBind &bind : binds) {
        bind.callback(deltaTime);
    }
}