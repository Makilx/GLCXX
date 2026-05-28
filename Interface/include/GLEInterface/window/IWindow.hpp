#pragma once

#include <GLECore/enum/window.hpp>
#include <GLECore/math/size2D.hpp>
#include <GLECore/pch.hpp>

namespace gle::backend {
    class IWindow {
      public:
        IWindow(WindowAPI api) : currentAPI(api) {}
        virtual ~IWindow() { Terminate(); }
        virtual void Init();
        virtual void Terminate();

      public:
        virtual Size2D GetSize() const = 0;
        virtual std::string GetTitle() const = 0;
        WindowAPI GetAPI() const { return currentAPI; }

      public:
        virtual void SetSize(Size2D size) = 0;
        virtual void SetTitle(std::string title) = 0;
        virtual void Close() = 0;
        virtual void SwapBuffers() = 0;
        virtual void PollForInput() = 0;
        virtual bool ShouldClose() = 0;

      private:
        WindowAPI currentAPI;
    };
} // namespace gle::backend