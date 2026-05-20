#pragma once

#include <GLECore/event/event.hpp>

namespace gle {
    class EventDispatcher {
      public:
        EventDispatcher(Event &event) : e(event) {}

        template <typename EventType, typename Callback>
        bool Dispatch(Callback callback) {
            if (e.IsA<EventType>()) {
                e.MarkHandled();
                callback(static_cast<EventType *>(e));
            }
            return false;
        }

      private:
        Event &e;
    };
} // namespace gle