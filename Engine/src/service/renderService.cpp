#include <GLEngine/service/renderService.hpp>

void gle::RenderService::OnInit() {
    // Create the renderer TODO:
    switch (api) {
    case gle::RenderAPI::OpenGL:
        break;
    case gle::RenderAPI::Vulkan:
        break;
    }

    // Create the renderer shaders

    // Create window
    worldRenderer->Init(NULL);
}

void gle::RenderService::OnUpdate(double deltaTime) {
    // Renderer loop

    // World
    worldRenderer->BeginFrame();
    worldRenderer->EndFrame();
    worldRenderer->Flush();
}

void gle::RenderService::OnTerminate() {
    // Delete the renderer
    worldRenderer->Terminate();
    delete worldRenderer;
}