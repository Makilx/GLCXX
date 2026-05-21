#pragma once

#include <GLECore/math/color.hpp>
#include <GLECore/math/matrix4.hpp>
#include <GLECore/math/vector.hpp>
#include <GLECore/pch.hpp>

namespace gle::backend {
    class IShader {
      public:
        virtual ~IShader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void Set(std::string_view name, int value) = 0;
        virtual void Set(std::string_view name, float value) = 0;
        virtual void Set(std::string_view name, const Vec2 &value) = 0;
        virtual void Set(std::string_view name, const Vec3 &value) = 0;
        virtual void Set(std::string_view name, const Vec4 &value) = 0;
        virtual void Set(std::string_view name, const Mat4 &value) = 0;
        virtual void Set(std::string_view name, const Color &value) = 0;
    };
} // namespace gle::backend