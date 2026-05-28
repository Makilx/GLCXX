#pragma once

#include <GLECore/pch.hpp>
#include <GLEInterface/window/IWindow.hpp>

namespace gle::backend {
    class GLFWWindow : public IWindow {
      public:
        GLFWWindow(std::string title, Size2D size) : IWindow(WindowAPI::GLFW), windowSize(size), windowTitle(title) {}
        void Init() override;
        void Terminate() override;

      public:
        Size2D GetSize() const override { return windowSize; }
        std::string GetTitle() const override { return windowTitle; }

      public:
        virtual void SetSize(Size2D size) override;
        virtual void SetTitle(std::string title) override;
        virtual void Close() override;
        virtual void SwapBuffers() override;
        virtual void PollForInput() override;
        virtual bool ShouldClose() override;

      private:
        Size2D windowSize;
        std::string windowTitle;
    };
} // namespace gle::backend