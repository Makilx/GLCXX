#pragma once

#include <GLECore/core.hpp>

namespace gle::backend {
    class IShader {
      public:
        virtual ~IShader() = default;
        virtual void Load() = 0;
        virtual void Unload() = 0;

      public:
        virtual void Use() const = 0;

        virtual void LoadShader(ShaderType type, const std::string &source) = 0;
        virtual bool Compile() = 0;
        virtual bool IsCompiled() const = 0;

        virtual void Set(const std::string &name, const float value) = 0;
        virtual void Set(const std::string &name, const int value) = 0;
        virtual void Set(const std::string &name, const Vec2 &value) = 0;
        virtual void Set(const std::string &name, const Vec3 &value) = 0;
        virtual void Set(const std::string &name, const Vec4 &value) = 0;
        virtual void Set(const std::string &name, const Size2D &value) = 0;
        virtual void Set(const std::string &name, const Mat4 &value) = 0;
        virtual void Set(const std::string &name, const Color &value) = 0;
    };
} // namespace gle::backend