#pragma once

#include <GLEInterface/components/IMesh.hpp>
#include <GLEngine/instance/instance.hpp>

namespace gle {
    class RenderService;
    class BasePart : public Instance {
      public:
        using Instance::Instance;
        BasePart() { SetVisibility(true); }
        virtual ~BasePart() = default;

        void SetVisibility(bool visible) {
            if (this->visible == visible)
                return;

            this->visible = visible;

            if (!GetParent())
                return;

            auto it = FindOnList();

            if (visible && it == visibleBaseparts.end()) {
                visibleBaseparts.push_back(this);
            } else if (!visible && it != visibleBaseparts.end()) {
                *it = visibleBaseparts.back();
                visibleBaseparts.pop_back();
            }
        }

        bool IsVisible() const { return visible; }

      protected:
        std::unique_ptr<backend::IMesh> partMesh;

      protected:
        void OnLoad() override {
            if (visible && FindOnList() == visibleBaseparts.end()) {
                visibleBaseparts.push_back(this);
            }
        }

        void OnUnload() override {
            auto it = FindOnList();

            if (it != visibleBaseparts.end()) {
                *it = visibleBaseparts.back();
                visibleBaseparts.pop_back();
            }
        }

      private:
        bool visible = false;

      private:
        static std::vector<BasePart *> visibleBaseparts;

      private:
        using VisibleIterator = std::vector<BasePart *>::iterator;

        VisibleIterator FindOnList() { return std::find(visibleBaseparts.begin(), visibleBaseparts.end(), this); }

        friend class RenderService;
    };
} // namespace gle