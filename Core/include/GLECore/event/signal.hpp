#pragma once

#include <GLECore/event/event.hpp>
#include <cstddef>
#include <functional>
#include <unordered_map>

namespace gle {
    template <typename EventType>
    class Signal {
      public:
        using Listener = std::function<void(EventType &)>;
        static_assert(std::is_base_of<Event, EventType>::value, "Event type must inherit from Event struct");

        size_t Subscribe(Listener listener) {
            const size_t id = ++idCount;
            listeners.insert({id, listener});
            return id;
        }
        template <typename T>
        size_t Subscribe(T *instance, void (T::*method)(EventType &)) {
            const size_t id = ++idCount;
            listeners.insert({id, [=](EventType &event) { (instance->*method)(event); }});
            return id;
        }
        void Unsubscribe(size_t id) { listeners.erase(id); }
        void UnsubscribeAll() { listeners.clear(); }
        void Fire(EventType &event) {
            if (listeners.size() == 0)
                return;
            for (Listener &l : listeners) {
                l(event);
                if (event.IsHandled())
                    break;
            }
        }

      private:
        std::unordered_map<size_t, Listener> listeners;
        size_t idCount = 0;
    };
} // namespace gle