#pragma once

#include <GLECore/math/math.hpp>
#include <GLECore/pch.hpp>

namespace gle {
    struct Color {
      public:
        float r, g, b, a;

        // Constructors
        constexpr Color() : r(0), g(0), b(0), a(0) {}
        constexpr Color(const float v, const float a = 1.0f) : r(v), g(v), b(v), a(a) {}
        constexpr Color(const float r, const float g, const float b, const float a = 1.0f) : r(r), g(g), b(b), a(a) {}
        static Color FromRGB(const float v) {
            return Color(Math::Saturate(v / 255.0f), Math::Saturate(v / 255.0f), Math::Saturate(v / 255.0f));
        }
        static Color FromRGB(const float r, const float g, const float b) {
            return Color(Math::Saturate(r / 255.0f), Math::Saturate(g / 255.0f), Math::Saturate(b / 255.0f));
        }
        static Color FromHSV(float h, float s, float v) {
            h = h - Math::Floor(h / 360.0f) * 360.0f; // wrap to [0, 360)
            s = Math::Saturate(s);
            v = Math::Saturate(v);

            float c = v * s;
            float hh = h / 60.0f;
            float x = c * (1.0f - Math::Abs(std::fmod(hh, 2.0f) - 1.0f));
            float m = v - c;

            float r = 0, g = 0, b = 0;

            if (hh < 1.0f) {
                r = c;
                g = x;
            } else if (hh < 2.0f) {
                r = x;
                g = c;
            } else if (hh < 3.0f) {
                g = c;
                b = x;
            } else if (hh < 4.0f) {
                g = x;
                b = c;
            } else if (hh < 5.0f) {
                r = x;
                b = c;
            } else {
                r = c;
                b = x;
            }

            return Color(Math::Saturate(r + m), Math::Saturate(g + m), Math::Saturate(b + m), 1.0f);
        }
        static Color FromHEX(const std::string hexCode) {
            std::string hex = hexCode;

            if (hex.empty())
                return Color();

            if (hex[0] == '#')
                hex = hex.substr(1);

            auto hexToVal = [](char c) -> float {
                if (c >= '0' && c <= '9')
                    return float(c - '0');
                if (c >= 'a' && c <= 'f')
                    return float(c - 'a' + 10);
                if (c >= 'A' && c <= 'F')
                    return float(c - 'A' + 10);
                return 0.0f;
            };

            auto byte = [&](int i) -> float { return (hexToVal(hex[i]) * 16.0f + hexToVal(hex[i + 1])) / 255.0f; };

            auto nibble = [&](int i) -> float {
                float v = hexToVal(hex[i]);
                return (v * 16.0f + v) / 255.0f;
            };

            float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;

            switch (hex.size()) {
            case 3: // RGB
                r = nibble(0);
                g = nibble(1);
                b = nibble(2);
                break;

            case 4: // RGBA
                r = nibble(0);
                g = nibble(1);
                b = nibble(2);
                a = nibble(3);
                break;

            case 6: // RRGGBB
                r = byte(0);
                g = byte(2);
                b = byte(4);
                break;

            case 8: // RRGGBBAA
                r = byte(0);
                g = byte(2);
                b = byte(4);
                a = byte(6);
                break;

            default:
                break;
            }

            return Color(r, g, b, a);
        }

        // Presets
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color White;
        static const Color Black;
        static const Color Clear;
        static const Color Yellow;
        static const Color Cyan;
        static const Color Magenta;
        static const Color Gray;

        // Types
        struct HSV {
            float h, s, v;
        };

        // Methods
        constexpr Color Mix(const Color &c, float m) const {
            return {
                Math::Lerp(r, c.r, m),
                Math::Lerp(g, c.g, m),
                Math::Lerp(b, c.b, m),
                Math::Lerp(a, c.a, m),
            };
        }
        constexpr Color::HSV ToHSV() const {
            float max = Math::Max(r, Math::Max(g, b));
            float min = Math::Min(r, Math::Min(g, b));
            float delta = max - min;

            HSV out{};
            out.v = max;

            if (delta < 1e-6f) {
                out.h = 0.0f;
                out.s = 0.0f;
                return out;
            }

            out.s = (max == 0.0f) ? 0.0f : (delta / max);

            if (max == r) {
                out.h = (g - b) / delta;
            } else if (max == g) {
                out.h = 2.0f + (b - r) / delta;
            } else {
                out.h = 4.0f + (r - g) / delta;
            }

            out.h *= 60.0f;

            if (out.h < 0.0f)
                out.h += 360.0f;

            // normalize to [0,1]
            out.h /= 360.0f;

            return out;
        }
        std::string ToHEX() const {
            auto toByte = [](float v) -> int {
                v = Math::Saturate(v);
                return (int)(v * 255.0f + 0.5f);
            };

            static const char *hex = "0123456789ABCDEF";

            char out[10]; // #RRGGBB + null safety
            int r8 = toByte(r);
            int g8 = toByte(g);
            int b8 = toByte(b);
            int a8 = toByte(a);

            out[0] = '#';

            out[1] = hex[r8 >> 4];
            out[2] = hex[r8 & 15];

            out[3] = hex[g8 >> 4];
            out[4] = hex[g8 & 15];

            out[5] = hex[b8 >> 4];
            out[6] = hex[b8 & 15];

            // Always include alpha for consistency (faster, branchless)
            out[7] = hex[a8 >> 4];
            out[8] = hex[a8 & 15];

            return std::string(out, 9);
        }

        // Presets
        static inline constexpr Color Red{1.0f, 0.0f, 0.0f, 1.0f};
        static inline constexpr Color Green{0.0f, 1.0f, 0.0f, 1.0f};
        static inline constexpr Color Blue{0.0f, 0.0f, 1.0f, 1.0f};
        static inline constexpr Color White{1.0f, 1.0f, 1.0f, 1.0f};
        static inline constexpr Color Black{0.0f, 0.0f, 0.0f, 1.0f};
        static inline constexpr Color Clear{0.0f, 0.0f, 0.0f, 0.0f};
        static inline constexpr Color Yellow{1.0f, 1.0f, 0.0f, 1.0f};
        static inline constexpr Color Cyan{0.0f, 1.0f, 1.0f, 1.0f};
        static inline constexpr Color Magenta{1.0f, 0.0f, 1.0f, 1.0f};
        static inline constexpr Color Gray{0.5f, 0.5f, 0.5f, 1.0f};

        // Misc
        std::string ToString() const { return ToHEX(); }
    };


} // namespace gle