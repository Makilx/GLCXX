#pragma once

#include <GLECore/pch.hpp>
#include <GLECore/type/property.hpp>

namespace gle {
    class Instance {
      public:
        Instance(Instance *parent = NULL);
        Instance(std::string name, Instance *parent = NULL);
        virtual ~Instance() = default;

      public:
        template <typename T>
        T *As() {
            return dynamic_cast<T *>(this);
        }
        virtual bool IsA(std::string className) const { return className == GetClassName(); };
        virtual std::string GetClassName() const { return "Instance"; }
        bool IsActive() const { return active; }
        std::string GetName() const { return name; }
        Instance *GetParent() const { return parent; }
        size_t GetUniqueID() const { return uniqueID; }

      public:
        std::vector<Instance *> GetChildren() const { return children; }
        std::vector<Instance *> GetDescendants() const;
        std::vector<Instance *> GetAncestors() const;
        std::vector<Instance *> GetChildrenNamed(const std::string &name) const;
        std::vector<Instance *> GetDescendantsNamed(const std::string &name) const;
        std::vector<Instance *> GetAncestorsNamed(const std::string &name) const;
        std::vector<Instance *> GetChildrenWhichIsA(const std::string &className) const;
        std::vector<Instance *> GetDescendantsWhichIsA(const std::string &className) const;
        std::vector<Instance *> GetAncestorsWhichIsA(const std::string &className) const;

      public:
        Instance *FindFirstChildNamed(const std::string &name) const;
        Instance *FindFirstDescendantsNamed(const std::string &name) const;
        Instance *FindFirstAncestorNamed(const std::string &name) const;
        Instance *FindFirstChildWhichIsA(const std::string &className) const;
        Instance *FindFirstDescendantsWhichIsA(const std::string &className) const;
        Instance *FindFirstAncestorWhichIsA(const std::string &className) const;

      public:
        void Destroy();
        void SetParent(Instance *parent);
        void ClearAllChildren() const;
        void SetActive(bool active);
        void Rename(std::string name);

      public:
        static Instance *GetInstanceByID(size_t id);
        static void ClearAllInstances();

      protected:
        bool canBeRenamed = true;
        bool canBeMoved = true;
        bool canBeDestroyed = true;

      protected:
        virtual void Register() = 0;
        virtual void OnLoad() {}
        virtual void OnUnload() {}
        virtual void OnChildAdded(Instance *child) {}
        virtual void OnChildRemoved(Instance *child) {}
        virtual void OnActiveSet(bool active) {}

      private:
        size_t uniqueID = 0;
        std::string name = "NULL";
        Instance *parent = NULL;
        std::vector<Instance *> children;
        bool active = true;
        bool destroyed = false;

      private:
        static std::unordered_map<size_t, Instance *> allInstances;

      private:
        void AddChild(Instance *child);
        void RemoveChild(Instance *child);
        size_t GenerateUniqueID() {
            static size_t gID = 0;
            return gID++;
        }
    };
} // namespace gle