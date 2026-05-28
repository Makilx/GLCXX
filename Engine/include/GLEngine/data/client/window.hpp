#pragma once

#include <GLECore/enum/window.hpp>
#include <GLECore/math/size2D.hpp>
#include <GLEInterface/window/IWindow.hpp>

namespace gle {
    class WindowController {
      public:
        WindowController(WindowAPI api) : currentAPI(api) {}

      public:
        void Resize(Size2D newSize) { window->SetSize(newSize); }
        void Close() { window->Close(); }
        void SetTitle(std::string title) { window->SetTitle(title); }
        std::string GetTitle() const { return window->GetTitle(); }
        Size2D GetSize() const { return window->GetSize(); }
        void SetFullscreen(bool fullscreen) {}
        bool IsFullscreen() const { return isFulscreen; }
        WindowAPI GetWindowAPI() const { return currentAPI; }

      private:
        bool isFulscreen = false;
        std::unique_ptr<backend::IWindow> window;
        WindowAPI currentAPI;
    };
} // namespace gle