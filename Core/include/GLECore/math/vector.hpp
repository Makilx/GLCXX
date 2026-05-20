#pragma once

#include <GLECore/math/math.hpp>
#include <GLECore/pch.hpp>

namespace gle {
    struct Vec2;
    struct Vec3;
    struct Vec4;

    // VEC2
    struct Vec2 {
      public:
        float x, y;

        // Constructors
        constexpr Vec2() : x(0), y(0) {}
        constexpr Vec2(const float v) : x(v), y(v) {}
        constexpr Vec2(const float x, const float y) : x(x), y(y) {}

        // Operators
        constexpr Vec2 operator-() const { return {-x, -y}; }
        constexpr Vec2 operator+(const Vec2 &v) const { return {x + v.x, y + v.y}; }
        constexpr Vec2 operator-(const Vec2 &v) const { return {x - v.x, y - v.y}; }
        constexpr Vec2 operator*(const Vec2 &v) const { return {x * v.x, y * v.y}; }
        constexpr Vec2 operator/(const Vec2 &v) const { return {x / v.x, y / v.y}; }
        constexpr Vec2 operator*(const float s) const { return {x * s, y * s}; }
        constexpr Vec2 operator/(const float s) const { return {x / s, y / s}; }
        constexpr Vec2 &operator+=(const Vec2 &v) {
            x += v.x;
            y += v.y;
            return *this;
        }
        constexpr Vec2 &operator-=(const Vec2 &v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }
        constexpr Vec2 &operator*=(const Vec2 &v) {
            x *= v.x;
            y *= v.y;
            return *this;
        }
        constexpr Vec2 &operator/=(const Vec2 &v) {
            x /= v.x;
            y /= v.y;
            return *this;
        }
        constexpr Vec2 &operator*=(const float s) {
            x *= s;
            y *= s;
            return *this;
        }
        constexpr Vec2 &operator/=(const float s) {
            x /= s;
            y /= s;
            return *this;
        }
        constexpr bool operator==(const Vec2 &v) const { return x == v.x && y == v.y; }
        constexpr bool operator!=(const Vec2 &v) const { return x != v.x || y != v.y; }
        constexpr bool operator>=(const Vec2 &v) const { return Magnitude() >= v.Magnitude(); }
        constexpr bool operator<=(const Vec2 &v) const { return Magnitude() <= v.Magnitude(); }
        constexpr bool operator>(const Vec2 &v) const { return Magnitude() > v.Magnitude(); }
        constexpr bool operator<(const Vec2 &v) const { return Magnitude() < v.Magnitude(); }
        constexpr bool operator==(const float s) const { return Magnitude() > s; }
        constexpr bool operator!=(const float s) const { return Magnitude() > s; }
        constexpr bool operator>=(const float s) const { return Magnitude() > s; }
        constexpr bool operator<=(const float s) const { return Magnitude() > s; }
        constexpr bool operator>(const float s) const { return Magnitude() > s; }
        constexpr bool operator<(const float s) const { return Magnitude() > s; }

        // Methods
        constexpr float Magnitude() const { return Math::Sqrt(x * x + y * y); }
        constexpr float MagnitudeSquared() const { return x * x + y * y; }
        constexpr Vec2 Lerp(const Vec2 &v, const float t) const { return Math::Lerp(*this, v, t); }
        constexpr float Dot(const Vec2 &v) const { return x * v.x + y * v.y; }
        constexpr float Distance(const Vec2 &v) const { return PointTo(v).Magnitude(); }
        constexpr Vec2 Normalized() const { return *this / Magnitude(); }
        constexpr Vec2 PointTo(const Vec2 &v) const { return (*this - v); }
        constexpr Vec2 Abs() { return {Math::Abs(x), Math::Abs(y)}; }
        constexpr Vec2 Clamp(const Vec2 &min, const Vec2 &max) const {
            return {Math::Clamp(x, min.x, max.x), Math::Clamp(y, min.y, max.y)};
        };

        // Misc
        std::string ToString() const { return std::to_string(x) + ", " + std::to_string(y); }
    };
    constexpr Vec2 operator*(float s, const Vec2 &v) {
        return {s * v.x, s * v.y};
    }
    constexpr Vec2 operator/(float s, const Vec2 &v) {
        return {s / v.x, s / v.y};
    }

    // VEC3
    struct Vec3 {
      public:
        float x, y, z;

        // Constructors
        constexpr Vec3() : x(0), y(0), z(0) {}
        constexpr Vec3(const float v) : x(v), y(v), z(v) {}
        constexpr Vec3(const float x, const float y) : x(x), y(y), z(0) {}
        constexpr Vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

        // Operators
        constexpr Vec3 operator-() const { return {-x, -y, -z}; }
        constexpr Vec3 operator+(const Vec3 &v) const { return {x + v.x, y + v.y, z + v.z}; }
        constexpr Vec3 operator-(const Vec3 &v) const { return {x - v.x, y - v.y, z - v.z}; }
        constexpr Vec3 operator*(const Vec3 &v) const { return {x * v.x, y * v.y, z * v.z}; }
        constexpr Vec3 operator/(const Vec3 &v) const { return {x / v.x, y / v.y, z / v.z}; }
        constexpr Vec3 operator*(const float s) const { return {x * s, y * s, z * s}; }
        constexpr Vec3 operator/(const float s) const { return {x / s, y / s, z / s}; }
        constexpr Vec3 &operator+=(const Vec3 &v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        constexpr Vec3 &operator-=(const Vec3 &v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        constexpr Vec3 &operator*=(const Vec3 &v) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }
        constexpr Vec3 &operator/=(const Vec3 &v) {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            return *this;
        }
        constexpr Vec3 &operator*=(const float s) {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }
        constexpr Vec3 &operator/=(const float s) {
            x /= s;
            y /= s;
            z /= s;
            return *this;
        }

        // Swizzle
        constexpr Vec2 xy() const { return {x, y}; }
        constexpr Vec2 xz() const { return {x, z}; }
        constexpr Vec2 yz() const { return {y, z}; }

        constexpr Vec2 yx() const { return {y, x}; }
        constexpr Vec2 zx() const { return {z, x}; }
        constexpr Vec2 zy() const { return {z, y}; }

        // 3-component swizzle (returns Vec3)
        constexpr Vec3 xyz() const { return {x, y, z}; }
        constexpr Vec3 xzy() const { return {x, z, y}; }
        constexpr Vec3 yxz() const { return {y, x, z}; }
        constexpr Vec3 yzx() const { return {y, z, x}; }
        constexpr Vec3 zxy() const { return {z, x, y}; }
        constexpr Vec3 zyx() const { return {z, y, x}; }

        // Methods
        constexpr float Magnitude() const { return Math::Sqrt(x * x + y * y + z * z); }
        constexpr float MagnitudeSquared() const { return x * x + y * y + z * z; }
        constexpr Vec3 Lerp(const Vec3 &v, const float t) const { return Math::Lerp(*this, v, t); }
        constexpr float Dot(const Vec3 &v) const { return x * v.x + y * v.y + z * v.z; }
        constexpr Vec3 Cross(const Vec3 &v) const { return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x}; }
        constexpr float Distance(const Vec3 &v) const { return PointTo(v).Magnitude(); }
        constexpr Vec3 PointTo(const Vec3 &v) const { return (v - *this); }
        constexpr Vec3 Normalized() const {
            float mag = Magnitude();
            return (mag == 0.0f) ? Vec3() : (*this / mag);
        }
        constexpr Vec3 Reflect(const Vec3 &normal) const { return *this - normal * (2.0f * Dot(normal)); }
        constexpr Vec3 Abs() const { return {Math::Abs(x), Math::Abs(y), Math::Abs(z)}; }
        constexpr Vec3 Clamp(const Vec3 &min, const Vec3 &max) const {
            return {Math::Clamp(x, min.x, max.x), Math::Clamp(y, min.y, max.y), Math::Clamp(z, min.z, max.z)};
        }

        // Misc
        std::string ToString() const { return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z); }
    };
    constexpr Vec3 operator*(float s, const Vec3 &v) {
        return {s * v.x, s * v.y, s * v.z};
    }
    constexpr Vec3 operator/(float s, const Vec3 &v) {
        return {s / v.x, s / v.y, s / v.z};
    }

    // VEC4
    struct Vec4 {
      public:
        float x, y, z, w;

        // Constructors
        constexpr Vec4() : x(0), y(0), z(0), w(0) {}
        constexpr Vec4(const float v) : x(v), y(v), z(v), w(v) {}
        constexpr Vec4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}

        // Operators
        constexpr Vec4 operator-() const { return {-x, -y, -z, -w}; }
        constexpr Vec4 operator+(const Vec4 &v) const { return {x + v.x, y + v.y, z + v.z, w + v.w}; }
        constexpr Vec4 operator-(const Vec4 &v) const { return {x - v.x, y - v.y, z - v.z, w - v.w}; }
        constexpr Vec4 operator*(const Vec4 &v) const { return {x * v.x, y * v.y, z * v.z, w * v.w}; }
        constexpr Vec4 operator/(const Vec4 &v) const { return {x / v.x, y / v.y, z / v.z, w / v.w}; }
        constexpr Vec4 operator*(const float s) const { return {x * s, y * s, z * s, w * s}; }
        constexpr Vec4 operator/(const float s) const { return {x / s, y / s, z / s, w / s}; }
        constexpr Vec4 &operator+=(const Vec4 &v) {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this;
        }
        constexpr Vec4 &operator-=(const Vec4 &v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this;
        }
        constexpr Vec4 &operator*=(const Vec4 &v) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            w *= v.w;
            return *this;
        }
        constexpr Vec4 &operator/=(const Vec4 &v) {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            w /= v.w;
            return *this;
        }
        constexpr Vec4 &operator*=(const float s) {
            x *= s;
            y *= s;
            z *= s;
            w *= s;
            return *this;
        }
        constexpr Vec4 &operator/=(const float s) {
            x /= s;
            y /= s;
            z /= s;
            w /= s;
            return *this;
        }

        // Swizzle (2D)
        constexpr Vec2 xy() const { return {x, y}; }
        constexpr Vec2 xz() const { return {x, z}; }
        constexpr Vec2 xw() const { return {x, w}; }
        constexpr Vec2 yz() const { return {y, z}; }
        constexpr Vec2 yw() const { return {y, w}; }
        constexpr Vec2 zw() const { return {z, w}; }
        constexpr Vec2 yx() const { return {y, x}; }
        constexpr Vec2 zx() const { return {z, x}; }
        constexpr Vec2 wx() const { return {w, x}; }
        constexpr Vec2 zy() const { return {z, y}; }
        constexpr Vec2 wy() const { return {w, y}; }
        constexpr Vec2 wz() const { return {w, z}; }

        // Swizzle (3D)
        constexpr Vec3 xyz() const { return {x, y, z}; }
        constexpr Vec3 xzy() const { return {x, z, y}; }
        constexpr Vec3 xyw() const { return {x, y, w}; }
        constexpr Vec3 xwy() const { return {x, w, y}; }
        constexpr Vec3 yxz() const { return {y, x, z}; }
        constexpr Vec3 yzw() const { return {y, z, w}; }
        constexpr Vec3 zxy() const { return {z, x, y}; }
        constexpr Vec3 zwx() const { return {z, w, x}; }
        constexpr Vec3 wxy() const { return {w, x, y}; }
        constexpr Vec3 wyz() const { return {w, y, z}; }

        // Methods
        constexpr float Magnitude() const { return Math::Sqrt(x * x + y * y + z * z + w * w); }
        constexpr float MagnitudeSquared() const { return x * x + y * y + z * z + w * w; }
        constexpr Vec4 Lerp(const Vec4 &v, const float t) const { return Math::Lerp(*this, v, t); }
        constexpr float Dot(const Vec4 &v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }
        constexpr float Distance(const Vec4 &v) const { return (v - *this).Magnitude(); }
        constexpr Vec4 PointTo(const Vec4 &v) const { return v - *this; }
        constexpr Vec4 Normalized() const {
            float mag = Magnitude();
            return (mag == 0.0f) ? Vec4() : (*this / mag);
        }
        constexpr Vec4 Abs() const { return {Math::Abs(x), Math::Abs(y), Math::Abs(z), Math::Abs(w)}; }
        constexpr Vec4 Clamp(const Vec4 &min, const Vec4 &max) const {
            return {Math::Clamp(x, min.x, max.x), Math::Clamp(y, min.y, max.y), Math::Clamp(z, min.z, max.z),
                    Math::Clamp(w, min.w, max.w)};
        }

        // Misc
        std::string ToString() const {
            return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w);
        }
    };
    constexpr Vec4 operator*(float s, const Vec4 &v) {
        return {s * v.x, s * v.y, s * v.z, s * v.w};
    }
    constexpr Vec4 operator/(float s, const Vec4 &v) {
        return {s / v.x, s / v.y, s / v.z, s / v.w};
    }
} // namespace gle