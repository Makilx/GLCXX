#pragma once

#include <GLECore/core.hpp>
#include <GLEInterface/rendering/IMesh.hpp>
#include <GLEInterface/rendering/Material.hpp>
#include <GLEngine/instance/instance.hpp>

namespace gle {
    class BasePart : public Instance {
      public:
        using Instance::Instance;

      public:
        std::string GetClassName() const override { return "BasePart"; }

      public:
        Material material;
        Vec3 size;

        // Physics
        bool anchored = false;
        bool canCollide = true;
        bool canTouch = true;
        bool canQuery = true;
        float mass = 1;

      public:
        bool IsVisible() const {
            return GetParent() != NULL && IsActive() && material.baseColor.a < 1 && material.baseColor.a > 0;
        }

      protected:
        backend::IMesh partMesh;

      protected:
        void OnLoad() override { VisibleUpdate(); }
        void OnUnload() override { VisibleUpdate(); }
        void OnActiveSet(bool active) override { VisibleUpdate(); }

      private:
        static std::vector<BasePart *> allVisibleParts;

      private:
        void VisibleUpdate() {
            bool shouldBeVisible = (IsActive() && GetParent() && material.baseColor.a >= 0 &&
                                    material.baseColor.a < 1 && size != Vec3(0.0f, 0.0f, 0.0f));

            if (shouldBeVisible) {
                if (std::find(allVisibleParts.begin(), allVisibleParts.end(), this) != allVisibleParts.end())
                    return;
                else
                    allVisibleParts.push_back(this);
            } else {
                auto it = std::find(allVisibleParts.begin(), allVisibleParts.end(), this);
                if (it != allVisibleParts.end())
                    allVisibleParts.erase(it);
            }
        }

        friend class RenderService;
    };
} // namespace gle