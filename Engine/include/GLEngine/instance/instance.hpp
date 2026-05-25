#pragma once

#include <GLECore/pch.hpp>
#include <GLECore/type/property.hpp>
#include <cstddef>
#include <vector>

namespace gle {
    class Instance;
    class RenderService;
    class Workspace;

    // Events
    struct InstanceEvent : public Event {
      public:
        std::string ToString() const override { return "InstanceEvent"; }
        Instance *instance;
    };

    struct RenamedEvent : public Event {
      public:
        std::string ToString() const override { return "RenamedEvent: " + name; }
        std::string name;
    };

    // Base

    class Instance {
      public:
        Instance() : uniqueID(GenerateUniqueID()) {
            RegisterProperties();
            RegisterInstance();
        }
        Instance(Instance *parent) : uniqueID(GenerateUniqueID()) {
            RegisterProperties();
            RegisterInstance();
            SetParent(parent);
        }
        Instance(std::string name) : name(name), uniqueID(GenerateUniqueID()) {
            RegisterProperties();
            RegisterInstance();
        }
        Instance(std::string name, Instance *parent) : name(name), uniqueID(GenerateUniqueID()) {
            RegisterProperties();
            RegisterInstance();
            SetParent(parent);
        }
        ~Instance() { Destroy(); }

      public:
        std::string GetName() const { return name; }
        Instance *GetParent() const { return parent; }
        std::vector<Instance *> GetChildren() const { return children; }
        std::vector<Instance *> GetDescendants() const;
        std::vector<Instance *> GetAncestors() const;
        size_t GetUniqueID() const { return uniqueID; }
        std::string GetClassName() const { return className; }
        template <typename Type>
        Type *As() const {
            return dynamic_cast<Type *>(this);
        }
        bool IsA(std::string className) const { return IsAResponse(className); }

      public:
        Instance *FindFirstChildNamed(std::string name) const;
        Instance *FindFirstAncestorNamed(std::string name) const;
        Instance *FindFirstDescendantNamed(std::string name) const;
        Instance *FindFirstChildWhichIsA(std::string className) const;
        Instance *FindFirstAncestorWhichIsA(std::string className) const;
        Instance *FindFirstDescendantWhichIsA(std::string className) const;
        template <typename Type>
        Type *FindFirstChildWhichIsA() const;
        template <typename Type>
        Type *FindFirstAncestorWhichIsA() const;
        template <typename Type>
        Type *FindFirstDescendantWhichIsA() const;

      public:
        void SetParent(Instance *parent);
        void SetName(std::string name) {
            if (!canBeNamed)
                return;
            this->name = name;
            RenamedEvent event;
            event.name = name;
            Renamed.Fire(event);
        }
        void Destroy();
        void ClearChildren() {
            for (Instance *instance : children) {
                instance->Destroy();
            }
        }

      public:
        Signal<InstanceEvent> ParentChanged;
        Signal<InstanceEvent> ChildAdded;
        Signal<InstanceEvent> ChildRemoved;
        Signal<RenamedEvent> Renamed;
        Signal<BlankEvent> Destroyed;

      public:
        static Instance *GetInstance(size_t uniqueID) { return activeInstances[uniqueID]; }

      protected:
        std::string className = "";
        bool canBeMoved = true;
        bool canBeDestroyed = true;
        bool canBeNamed = true;

        virtual bool IsAResponse(std::string className) const { return this->className == className; }
        virtual void RegisterProperties() {}
        virtual void OnLoad() {}
        virtual void OnUnload() {}
        virtual void OnChildAdd(Instance *child) {}
        virtual void OnChildRemove(Instance *child) {}

      private:
        Instance *parent = NULL;
        std::vector<Instance *> children;
        std::string name = "";
        size_t uniqueID;
        std::unordered_map<std::string, PropertyBase> properties;
        bool destroyed = false;

      private:
        static std::unordered_map<size_t, Instance *> activeInstances;

      private:
        static void ClearAllActiveInstances() {
            for (auto &[id, instance] : activeInstances) {
                instance->Destroy();
            }
        }

      private:
        size_t GenerateUniqueID() {
            static size_t gID = 0;
            return gID++;
        }

        void AddChild(Instance *child) {
            children.push_back(child);
            OnChildAdd(child);
            InstanceEvent event;
            event.instance = child;
            ChildAdded.Fire(event);
        }
        void RemoveChild(Instance *child) {
            children.erase(std::find(children.begin(), children.end(), child));
            OnChildRemove(child);
            InstanceEvent event;
            event.instance = child;
            ChildRemoved.Fire(event);
        }
        void RegisterProperty(PropertyBase property, std::string name) { properties.insert({name, property}); }
        void RegisterInstance() { activeInstances.insert({uniqueID, this}); }

      private:
        friend class RenderService;
        friend class Workspace;
    };
} // namespace gle