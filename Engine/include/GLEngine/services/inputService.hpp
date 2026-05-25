#pragma once

#include <GLECore/math/vector.hpp>
#include <GLEngine/services/service.hpp>

namespace gle {
    enum class Key : unsigned int {
        Unknown = 0,

        Space,
        Apostrophe,
        Comma,
        Minus,
        Period,
        Slash,

        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,

        Semicolon,
        Equal,

        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        LeftBracket,
        Backslash,
        RightBracket,
        GraveAccent,

        Escape,
        Enter,
        Tab,
        Backspace,
        Insert,
        Delete,

        Right,
        Left,
        Down,
        Up,

        PageUp,
        PageDown,
        Home,
        End,

        CapsLock,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,

        KP0,
        KP1,
        KP2,
        KP3,
        KP4,
        KP5,
        KP6,
        KP7,
        KP8,
        KP9,

        KPDecimal,
        KPDivide,
        KPMultiply,
        KPSubtract,
        KPAdd,
        KPEnter,
        KPEqual,

        LeftShift,
        LeftControl,
        LeftAlt,
        LeftSuper,

        RightShift,
        RightControl,
        RightAlt,
        RightSuper,

        Menu
    };
    enum class MouseButton : unsigned int {
        Left = 0,
        Right = 1,
        Middle = 2,

        Button4 = 3,
        Button5 = 4,
        Button6 = 5,
        Button7 = 6,
        Button8 = 7
    };
    enum class GamepadButton : unsigned int {
        A = 0,
        B = 1,
        X = 2,
        Y = 3,

        LeftBumper = 4,
        RightBumper = 5,

        Back = 6,
        Start = 7,
        Guide = 8,

        LeftThumb = 9,
        RightThumb = 10,

        DPadUp = 11,
        DPadRight = 12,
        DPadDown = 13,
        DPadLeft = 14
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
        bool GetMouseButton(MouseButton button, InputState state = InputState::Holding);

      public:
        void SetCursorBehavior(CursorBehavior behavior);
        void SetMousePos(Vec2 pos);

      protected:
        void OnInit() override {}
        void OnUpdate(double deltaTime) override {}
        void OnTerminate() override {}
    };
} // namespace gle