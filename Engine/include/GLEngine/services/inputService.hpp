#pragma once

#include <GLECore/math/vector.hpp>
#include <GLEngine/services/service.hpp>

namespace gle {
    enum class Key : unsigned int {
    };
    enum class MouseButton : unsigned int {
    };
    enum class GamepadButton : unsigned int {
    };
    enum class InputState : unsigned int {
        Pressing = 0,
        Releasing = 1,
        Holding = 2
    };
    enum class InputType : unsigned int {
        Keyboard = 0,
        Mouse = 1,
        Gamepad = 2,
        Touch = 3
    };
    enum class CursorBehavior : unsigned int {
        Default = 0,
        Disabled = 1,
        Hidden = 2
    };

    class InputService : public Service {
      public:
        using Service::Service;

      public:
        Vec2 GetMousePos() const;
        Vec2 GetMouseDelta() const;
        CursorBehavior GetCursorBehavior() const;
        InputType GetLastInputType() const;
        bool GetKey(Key key, InputState state = InputState::Holding);
        bool GetKey(MouseButton button, InputState state = InputState::Holding);

      public:
        void SetCursorBehavior(CursorBehavior behavior);
        void SetMousePos(Vec2 pos);

      protected:
        void OnInit() override {}
        void OnUpdate(double deltaTime) override {}
        void OnTerminate() override {}

      private:
    };
} // namespace gle