#include <GLEngine/instance/instance.hpp>

// Search methods
std::vector<gle::Instance *> gle::Instance::GetDescendants() const {
    std::vector<Instance *> descendants;

    // Reserve current children count as a small optimization
    descendants.reserve(children.size());

    // Iterative DFS (faster + avoids recursion stack)
    std::vector<Instance *> stack = children;

    while (!stack.empty()) {
        Instance *current = stack.back();
        stack.pop_back();

        descendants.push_back(current);

        const std::vector<Instance *> &currentChildren = current->children;

        stack.insert(stack.end(), currentChildren.begin(), currentChildren.end());
    }

    return descendants;
}

std::vector<gle::Instance *> gle::Instance::GetAncestors() const {
    std::vector<Instance *> ancestors;

    Instance *current = parent;

    // Walk upward iteratively
    while (current) {
        ancestors.push_back(current);
        current = current->parent;
    }

    return ancestors;
}

gle::Instance *gle::Instance::FindFirstChildNamed(std::string name) const {
    for (Instance *child : children) {
        if (child->name == name)
            return child;
    }
    return NULL;
}

gle::Instance *gle::Instance::FindFirstAncestorNamed(std::string name) const {
    for (Instance *child : GetAncestors()) {
        if (child->name == name)
            return child;
    }
    return NULL;
}

gle::Instance *gle::Instance::FindFirstDescendantNamed(std::string name) const {
    for (Instance *child : GetDescendants()) {
        if (child->name == name)
            return child;
    }
    return NULL;
}

template <typename T>
T *gle::Instance::FindFirstChildWhichIsA() const {
    for (Instance *child : children) {
        if (child->As<T *>() != NULL)
            return child->As<T *>();
    }
    return NULL;
}

template <typename T>
T *gle::Instance::FindFirstAncestorWhichIsA() const {
    for (Instance *child : GetAncestors()) {
        if (child->As<T *>() != NULL)
            return child->As<T *>();
    }
    return NULL;
}

template <typename T>
T *gle::Instance::FindFirstDescendantWhichIsA() const {
    for (Instance *child : GetDescendants()) {
        if (child->As<T *>() != NULL)
            return child->As<T *>();
    }
    return NULL;
}

gle::Instance *gle::Instance::FindFirstChildWhichIsA(std::string className) const {
    for (Instance *child : children) {
        if (child->IsA(className)) {
            return child;
        }
    }
    return NULL;
}

gle::Instance *gle::Instance::FindFirstAncestorWhichIsA(std::string className) const {
    for (Instance *child : GetAncestors()) {
        if (child->IsA(className)) {
            return child;
        }
    }
    return NULL;
}

gle::Instance *gle::Instance::FindFirstDescendantWhichIsA(std::string className) const {
    for (Instance *child : GetDescendants()) {
        if (child->IsA(className)) {
            return child;
        }
    }
    return NULL;
}

// Main methods
void gle::Instance::SetParent(gle::Instance *parent) {
    if (this->parent) {
        OnUnload();
        this->parent->RemoveChild(this);
    }

    this->parent = parent;

    if (this->parent) {
        this->parent->AddChild(this);
        OnLoad();
    }

    InstanceEvent event;
    event.instance = parent;
    ParentChanged.Fire(event);
}

void gle::Instance::Destroy() {
    // Set parent
    if (destroyed)
        return;

    BlankEvent e;
    Destroyed.Fire(e);

    // Set parent
    SetParent(NULL);

    // Clear all children
    for (Instance *child : children) {
        child->Destroy();
    }

    // Remove from global
    activeInstances.erase(uniqueID);

    destroyed = true;
}