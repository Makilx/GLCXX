#pragma once

namespace gle {
    enum class RenderMode : unsigned int {
        Default = 0,
        Wireframe = 1
    };

    enum class RenderAPI : unsigned int {
        OpenGL = 0,
        Vulkan = 1,
    };
} // namespace gle