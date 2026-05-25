#pragma once

#include <GLECore/math/vector.hpp>
#include <GLECore/pch.hpp>

namespace gle::backend {
    struct Vertex {
        Vec3 position;
        Vec2 textureCoords;
        Vec2 uv;
    };

    struct IMesh {
      public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    };
} // namespace gle::backend