#pragma once

#include <GLECore/math/vector.hpp>
#include <GLECore/pch.hpp>

namespace gle::backend {
    struct Vertex {
        Vec3 position;
        Vec3 normal;
        Vec2 uv;
    };

    struct MeshData {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    };

    struct IMesh {
      public:
        virtual ~IMesh() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual size_t GetVertexCount() const = 0;
        virtual size_t GetIndexCount() const = 0;
    };
} // namespace gle::backend