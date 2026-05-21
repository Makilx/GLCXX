#pragma once

#include <GLECore/math/size2D.hpp>
#include <GLECore/pch.hpp>

namespace gle::backend {

    class IWindow {
      public:
        virtual ~IWindow() = default;

        // Lifecycle
        virtual void Init() = 0;
        virtual void Destroy() = 0;

        // Title
        virtual void SetTitle(const std::string &title) = 0;
        virtual std::string GetTitle() const = 0;

        // State
        virtual bool ShouldClose() const = 0;
        virtual bool IsFocused() const = 0;
        virtual bool IsMinimized() const = 0;
        virtual bool IsVisible() const = 0;
        virtual bool IsFullscreen() const = 0;
        virtual void SetFullscreen() = 0;

        // Position
        virtual void SetPosition(const Size2D &position) = 0;
        virtual Size2D GetPosition() const = 0;

        // Rendering
        virtual void SwapBuffers() = 0;

        // Input
        virtual void PollInput() = 0;

        // Size
        virtual Size2D GetSize() const = 0;
        virtual void SetSize(const Size2D &size) = 0;

        // Window
        virtual void Close() = 0;
    };

} // namespace gle::backend