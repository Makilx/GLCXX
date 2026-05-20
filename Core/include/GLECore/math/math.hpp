#pragma once
#include <cmath>

namespace gle {
    class Math {
      public:
        // Constants
        static constexpr float PI = 3.14159265358979323846f;
        static constexpr float TAU = 6.28318530717958647692f;
        static constexpr float DEG2RAD = PI / 180.0f;
        static constexpr float RAD2DEG = 180.0f / PI;

        // -------------------------------------------------
        // Basic functions
        // -------------------------------------------------

        template <typename T>
        static constexpr T Min(T a, T b) {
            return (a < b) ? a : b;
        }

        template <typename T>
        static constexpr T Max(T a, T b) {
            return (a > b) ? a : b;
        }

        template <typename T>
        static constexpr T Clamp(T value, T minVal, T maxVal) {
            return Max(minVal, Min(value, maxVal));
        }

        template <typename T>
        static constexpr T Abs(T v) {
            return (v < 0) ? -v : v;
        }

        template <typename T>
        static constexpr T Sign(T v) {
            return (v > 0) - (v < 0);
        }

        template <typename T>
        static constexpr T Lerp(T a, T b, float t) {
            return a + (b - a) * t;
        }

        template <typename T>
        static constexpr T Square(T v) {
            return v * v;
        }

        template <typename T>
        static constexpr T Cube(T v) {
            return v * v * v;
        }

        // -------------------------------------------------
        // Floating point helpers
        // -------------------------------------------------

        static constexpr bool NearlyEqual(float a, float b, float epsilon = 0.00001f) { return Abs(a - b) <= epsilon; }

        static constexpr float Saturate(float v) { return Clamp(v, 0.0f, 1.0f); }

        static float Floor(float v) { return std::floor(v); }

        static float Ceil(float v) { return std::ceil(v); }

        static float Round(float v) { return std::round(v); }

        static float Fract(float v) { return v - Floor(v); }

        // -------------------------------------------------
        // Trig
        // -------------------------------------------------

        static float Sin(float rads) { return std::sin(rads); }

        static float Cos(float rads) { return std::cos(rads); }

        static float Tan(float rads) { return std::tan(rads); }

        static float Asin(float v) { return std::asin(v); }

        static float Acos(float v) { return std::acos(v); }

        static float Atan(float v) { return std::atan(v); }

        static float Atan2(float y, float x) { return std::atan2(y, x); }

        // -------------------------------------------------
        // Power
        // -------------------------------------------------

        static float Sqrt(float v) { return std::sqrt(v); }

        static float Pow(float base, float exp) { return std::pow(base, exp); }

        static float Exp(float v) { return std::exp(v); }

        static float Log(float v) { return std::log(v); }

        // -------------------------------------------------
        // Conversion
        // -------------------------------------------------

        static constexpr float Rad(float degrees) { return degrees * DEG2RAD; }

        static constexpr float Deg(float radians) { return radians * RAD2DEG; }
    };

} // namespace gle