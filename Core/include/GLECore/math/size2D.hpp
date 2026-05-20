#pragma once

#include <GLECore/math/math.hpp>
#include <GLECore/math/vector.hpp>
#include <GLECore/pch.hpp>

namespace gle {
    struct Size2D {
      public:
        size_t width, height;

        // Constructors
        constexpr Size2D() : width(0), height(0) {}
        constexpr Size2D(const size_t v) : width(v), height(v) {}
        constexpr Size2D(const size_t x, const size_t y) : width(x), height(y) {}
        explicit constexpr Size2D(const Vec2 &v)
            : width(Math::Max((size_t)Math::Round(v.x), (size_t)0)),
              height(Math::Max((size_t)Math::Round(v.y), (size_t)0)) {}

        // Operators
        constexpr Size2D operator+(const Size2D &s) const { return {width + s.width, height + s.height}; }
        constexpr Size2D operator-(const Size2D &s) const { return {width - s.width, height - s.height}; }
        constexpr Size2D operator*(const Size2D &s) const { return {width * s.width, height * s.height}; }
        constexpr Size2D operator/(const Size2D &s) const { return {width / s.width, height / s.height}; }
        constexpr Size2D operator*(const float s) const { return {(size_t)(width * s), (size_t)(height * s)}; }
        constexpr Size2D operator/(const float s) const { return {(size_t)(width / s), (size_t)(height / s)}; }
        constexpr Size2D &operator+=(const Size2D &s) {
            width += s.width;
            height += s.height;
            return *this;
        }
        constexpr Size2D &operator-=(const Size2D &s) {
            width -= s.width;
            height -= s.height;
            return *this;
        }
        constexpr Size2D &operator*=(const Size2D &s) {
            width *= s.width;
            height *= s.height;
            return *this;
        }
        constexpr Size2D &operator/=(const Size2D &s) {
            width /= s.width;
            height /= s.height;
            return *this;
        }
        constexpr Size2D &operator*=(const float s) {
            width *= s;
            height *= s;
            return *this;
        }
        constexpr Size2D &operator/=(const float s) {
            width /= s;
            height /= s;
            return *this;
        }
        constexpr bool operator==(const Size2D &s) const { return width == s.width && height == s.height; }
        constexpr bool operator!=(const Size2D &s) const { return width != s.width || height != s.height; }
        constexpr bool operator>=(const Size2D &s) const { return Area() >= s.Area(); }
        constexpr bool operator<=(const Size2D &s) const { return Area() <= s.Area(); }
        constexpr bool operator>(const Size2D &s) const { return Area() > s.Area(); }
        constexpr bool operator<(const Size2D &s) const { return Area() < s.Area(); }

        // Methods
        constexpr size_t Area() const { return width * height; }
        constexpr Vec2 ToVec2() const { return {(float)width, (float)height}; }

        // Misc
        std::string ToString() const { return std::to_string(width) + ", " + std::to_string(height); }
    };
    constexpr Size2D operator*(const float s, const Size2D &v) {
        return {(size_t)(v.width * s), (size_t)(v.height * s)};
    };
    constexpr Size2D operator/(const float s, const Size2D &v) {
        return {(size_t)(v.width / s), (size_t)(v.height / s)};
    }
} // namespace gle