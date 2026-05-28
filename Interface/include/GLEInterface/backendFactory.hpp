#pragma once

#include <GLECore/pch.hpp>
#include <GLEInterface/input/IInput.hpp>
#include <GLEInterface/rendering/IRenderer.hpp>
#include <GLEInterface/window/IWindow.hpp>

namespace gle::backend {
    class BackendFactory {
      public:
        IWindow *createWindow(WindowAPI api);
        IRenderer *createRenderer(RenderAPI api, IWindow *window);
        IInput *createInput(WindowAPI api, IWindow *window);
    };
} // namespace gle::backend