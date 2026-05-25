#pragma once

#include <GLECore/enum/input.hpp>
#include <GLECore/event/signal.hpp>
#include <GLECore/math/vector.hpp>
#include <GLECore/pch.hpp>
#include <GLEInterface/window/IWindow.hpp>

namespace gle {
    struct KeyEvent : public Event {
      public:
        std::string ToString() const override { return "KeyEvent"; }
        Key key;
        InputState state;
    };

    struct MouseButtonEvent : public Event {
      public:
        std::string ToString() const override { return "MouseButtonEvent"; }
        MouseButton button;
        InputState state;
    };

    struct MouseWheelEvent : public Event {
      public:
        std::string ToString() const override { return "MouseWheelEvent"; }
        float delta;
    };

    struct GamepadButtonEvent : public Event {
      public:
        std::string ToString() const override { return "GamepadButtonEvent"; }
        int gamepadId;
        GamepadButton button;
        InputState state;
    };

    struct MouseMovedEvent : public Event {
      public:
        std::string ToString() const override { return "MouseMovedEvent"; }
        Vec2 position;
        Vec2 delta;
    };

    namespace backend {
        class IInput {
          public:
            virtual ~IInput() = default;
            virtual void Init(IWindow *window) = 0;
            virtual void Terminate() = 0;
            virtual void Update() = 0;

          public:
            virtual float GetKey(Key key, InputState state) const = 0;
            virtual float GetMouseButton(MouseButton button, InputState state) const = 0;
            virtual float GetGamepadButton(int gamepadId, GamepadButton button) const = 0;
            virtual Vec2 GetGamepadThumbstick(int gamepadId, GamepadThumbstick thumbstick) const = 0;
            virtual Vec2 GetGamepadDPad(int gamepadId) const = 0;
            virtual Vec2 GetMouseLocation() const = 0;
            virtual Vec2 GetMouseDelta() const = 0;
            virtual CursorBehavior GetCursorBehavior() const = 0;
            virtual InputType GetLastInputType() const = 0;
            virtual float GetMouseWheelDelta() const = 0;

          public:
            virtual void SetCursorBehavior(CursorBehavior behavior) = 0;

          public:
            Signal<GamepadButtonEvent> OnGamepadButtonChanged;
            Signal<KeyEvent> OnKeyChanged;
            Signal<MouseButtonEvent> OnMouseButtonChanged;
            Signal<MouseMovedEvent> OnMouseMoved;
            Signal<MouseWheelEvent> OnMouseWheelChanged;
        };
    } // namespace backend
} // namespace gle