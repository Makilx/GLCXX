#pragma once

#include <GLECore/math/math.hpp>
#include <GLECore/math/vector.hpp>

namespace gle {

    struct Mat4 {
        float m[16] = {0};

        // Access helper (column-major)
        float &operator()(int row, int col) { return m[col * 4 + row]; }

        const float &operator()(int row, int col) const { return m[col * 4 + row]; }

        // Identity
        static Mat4 Identity() {
            Mat4 r;
            r(0, 0) = 1;
            r(1, 1) = 1;
            r(2, 2) = 1;
            r(3, 3) = 1;
            return r;
        }

        // Translation
        static Mat4 Translation(const Vec3 &t) {
            Mat4 r = Identity();
            r(0, 3) = t.x;
            r(1, 3) = t.y;
            r(2, 3) = t.z;
            return r;
        }

        // Scale
        static Mat4 Scale(const Vec3 &s) {
            Mat4 r = Identity();
            r(0, 0) = s.x;
            r(1, 1) = s.y;
            r(2, 2) = s.z;
            return r;
        }

        // From CFrame basis (this is the magic one)
        static Mat4 FromBasis(const Vec3 &right, const Vec3 &up, const Vec3 &forward, const Vec3 &pos) {
            Mat4 r = Identity();

            r(0, 0) = right.x;
            r(1, 0) = right.y;
            r(2, 0) = right.z;
            r(0, 1) = up.x;
            r(1, 1) = up.y;
            r(2, 1) = up.z;
            r(0, 2) = forward.x;
            r(1, 2) = forward.y;
            r(2, 2) = forward.z;

            r(0, 3) = pos.x;
            r(1, 3) = pos.y;
            r(2, 3) = pos.z;

            return r;
        }

        // Matrix multiply
        Mat4 operator*(const Mat4 &o) const {
            Mat4 r;

            for (int c = 0; c < 4; ++c)
                for (int r1 = 0; r1 < 4; ++r1)
                    for (int k = 0; k < 4; ++k)
                        r(r1, c) += (*this)(r1, k) * o(k, c);

            return r;
        }

        // Perspective projection
        static Mat4 Perspective(float fovRad, float aspect, float near, float far) {
            Mat4 r;

            float f = 1.0f / std::tan(fovRad * 0.5f);

            r(0, 0) = f / aspect;
            r(1, 1) = f;
            r(2, 2) = (far + near) / (near - far);
            r(2, 3) = (2 * far * near) / (near - far);
            r(3, 2) = -1.0f;

            return r;
        }

        // Orthographic projection
        static Mat4 Ortho(float left, float right, float bottom, float top, float near, float far) {
            Mat4 r = Identity();

            r(0, 0) = 2.0f / (right - left);
            r(1, 1) = 2.0f / (top - bottom);
            r(2, 2) = -2.0f / (far - near);

            r(0, 3) = -(right + left) / (right - left);
            r(1, 3) = -(top + bottom) / (top - bottom);
            r(2, 3) = -(far + near) / (far - near);

            return r;
        }

        const float *Data() const { return m; }
    };

} // namespace gle