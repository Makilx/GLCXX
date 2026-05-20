#pragma once

#include <GLECore/pch.hpp>

namespace gle {
    struct Event {
      public:
        virtual std::string ToString() const { return "Event"; }
        bool IsHandled() const { return handled; }
        void MarkHandled() { handled = true; }

        template <typename T>
        bool IsA() const {
            return dynamic_cast<T *>(this) != NULL;
        }

      private:
        bool handled = false;
    };

    struct BlankEvent : public Event {};
} // namespace gle