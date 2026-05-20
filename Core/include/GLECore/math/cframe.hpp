#pragma once

#include <GLECore/math/math.hpp>
#include <GLECore/math/matrix4.hpp>
#include <GLECore/math/vector.hpp>
#include <GLECore/pch.hpp>

namespace gle {
    class CFrame {
      public:
        Vec3 position;
        Vec3 right;
        Vec3 up;
        Vec3 forward;

        // Constructors
        constexpr CFrame() : position(0, 0, 0), right(1, 0, 0), up(0, 1, 0), forward(0, 0, 1) {}
        constexpr CFrame(Vec3 p, Vec3 r, Vec3 u, Vec3 f) : position(p), right(r), up(u), forward(f) {}
        static CFrame LookAt(Vec3 origin, Vec3 at, Vec3 worldUp = Vec3(0, 1, 0)) {
            Vec3 f = (at - origin).Normalized();
            Vec3 r = f.Cross(worldUp).Normalized();
            Vec3 u = r.Cross(f);

            return {origin, r, u, f};
        }
        static CFrame FromEulerAnglesYXZ(float y, float x, float z) {
            float cx = Math::Cos(x), sx = Math::Sin(x);
            float cy = Math::Cos(y), sy = Math::Sin(y);
            float cz = Math::Cos(z), sz = Math::Sin(z);

            Vec3 r{cy * cz + sy * sx * sz, cz * sy * sx - cy * sz, cx * sy};

            Vec3 u{cx * sz, cx * cz, -sx};

            Vec3 f{cy * sx * sz - cz * sy, sy * sz + cy * cz * sx, cx * cy};

            return {Vec3(0, 0, 0), r, u, f};
        }

        // Helpers
        inline Vec3 TransformVector(const Vec3 &v) const { return right * v.x + up * v.y + forward * v.z; }
        inline Vec3 TransformPoint(const Vec3 &p) const { return position + TransformVector(p); }

        // Operators
        CFrame operator*(const CFrame &b) const {
            CFrame r;
            r.right = TransformVector(b.right);
            r.up = TransformVector(b.up);
            r.forward = TransformVector(b.forward);
            r.position = TransformPoint(b.position);
            return r;
        }
        CFrame &operator*=(const CFrame &b) {
            *this = *this * b;
            return *this;
        }

        // Methods
        CFrame Inverse() const {
            Vec3 rT{right.x, up.x, forward.x};
            Vec3 uT{right.y, up.y, forward.y};
            Vec3 fT{right.z, up.z, forward.z};

            Vec3 p{-position.Dot(rT), -position.Dot(uT), -position.Dot(fT)};

            return {p, rT, uT, fT};
        }
        CFrame Lerp(const CFrame &b, float t) const {
            Vec3 pos = position.Lerp(b.position, t);

            Vec3 f = forward.Lerp(b.forward, t).Normalized();
            Vec3 r = f.Cross(up.Lerp(b.up, t)).Normalized();
            Vec3 u = r.Cross(f);

            return {pos, r, u, f};
        }
        Mat4 ToMat4() const { return Mat4::FromBasis(right, up, forward, position); }

        // Misc
        std::string ToString() const {
            return position.ToString() + ", " + right.ToString() + ", " + up.ToString() + ", " + forward.ToString();
        }
    };
} // namespace gle