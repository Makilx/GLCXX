#include <GLEngine/instance/instance.hpp>

// Constructors
gle::Instance::Instance(Instance *parent) {
    this->name = GetClassName();
    if (parent)
        SetParent(parent);
}
gle::Instance::Instance(std::string name, Instance *parent) {
    this->name = name;
    if (parent)
        SetParent(parent);
}

// Get Children
std::vector<gle::Instance *> gle::Instance::GetDescendants() const {
    std::vector<Instance *> result;

    std::vector<Instance *> stack;
    stack.reserve(children.size());

    for (Instance *child : children)
        stack.push_back(child);

    while (!stack.empty()) {
        Instance *current = stack.back();
        stack.pop_back();

        result.push_back(current);

        for (Instance *child : current->children)
            stack.push_back(child);
    }

    return result;
}
std::vector<gle::Instance *> gle::Instance::GetAncestors() const {
    std::vector<Instance *> result;

    Instance *current = parent;

    while (current) {
        result.push_back(current);
        current = current->parent;
    }

    return result;
}
std::vector<gle::Instance *> gle::Instance::GetChildrenNamed(const std::string &name) const {
    std::vector<Instance *> result;
    result.reserve(children.size());

    for (Instance *child : children) {
        if (child->name == name)
            result.push_back(child);
    }

    return result;
}
std::vector<gle::Instance *> gle::Instance::GetDescendantsNamed(const std::string &name) const {
    std::vector<Instance *> result;

    std::vector<Instance *> stack;
    stack.reserve(children.size());

    for (Instance *child : children)
        stack.push_back(child);

    while (!stack.empty()) {
        Instance *current = stack.back();
        stack.pop_back();

        if (current->name == name)
            result.push_back(current);

        for (Instance *child : current->children)
            stack.push_back(child);
    }

    return result;
}
std::vector<gle::Instance *> gle::Instance::GetAncestorsNamed(const std::string &name) const {
    std::vector<Instance *> result;

    Instance *current = parent;

    while (current) {
        if (current->name == name)
            result.push_back(current);

        current = current->parent;
    }

    return result;
}
std::vector<gle::Instance *> gle::Instance::GetChildrenWhichIsA(const std::string &className) const {
    std::vector<Instance *> result;
    result.reserve(children.size());

    for (Instance *child : children) {
        if (child->IsA(className))
            result.push_back(child);
    }

    return result;
}
std::vector<gle::Instance *> gle::Instance::GetDescendantsWhichIsA(const std::string &className) const {
    std::vector<Instance *> result;

    std::vector<Instance *> stack;
    stack.reserve(children.size());

    for (Instance *child : children)
        stack.push_back(child);

    while (!stack.empty()) {
        Instance *current = stack.back();
        stack.pop_back();

        if (current->IsA(className))
            result.push_back(current);

        for (Instance *child : current->children)
            stack.push_back(child);
    }

    return result;
}
std::vector<gle::Instance *> gle::Instance::GetAncestorsWhichIsA(const std::string &className) const {
    std::vector<Instance *> result;

    Instance *current = parent;

    while (current) {
        if (current->IsA(className))
            result.push_back(current);

        current = current->parent;
    }

    return result;
}

// Search methods
gle::Instance *gle::Instance::FindFirstChildNamed(const std::string &name) const {
    for (Instance *child : GetChildren()) {
        if (child->name == name)
            return child;
    }
    return NULL;
}
gle::Instance *gle::Instance::FindFirstDescendantsNamed(const std::string &name) const {
    for (Instance *child : GetDescendants()) {
        if (child->name == name)
            return child;
    }
    return NULL;
}
gle::Instance *gle::Instance::FindFirstAncestorNamed(const std::string &name) const {
    for (Instance *child : GetAncestors()) {
        if (child->name == name)
            return child;
    }
    return NULL;
}
gle::Instance *gle::Instance::FindFirstChildWhichIsA(const std::string &className) const {
    for (Instance *child : GetChildren()) {
        if (child->IsA(className))
            return child;
    }
    return NULL;
}
gle::Instance *gle::Instance::FindFirstDescendantsWhichIsA(const std::string &className) const {
    for (Instance *child : GetDescendants()) {
        if (child->IsA(className))
            return child;
    }
    return NULL;
}
gle::Instance *gle::Instance::FindFirstAncestorWhichIsA(const std::string &className) const {
    for (Instance *child : GetAncestors()) {
        if (child->IsA(className))
            return child;
    }
    return NULL;
}

// Other methods
void gle::Instance::Destroy() {
    if (!canBeDestroyed || destroyed)
        return;

    SetParent(NULL);
    ClearAllChildren();

    allInstances.erase(uniqueID);
    destroyed = true;
}
void gle::Instance::SetParent(gle::Instance *parent) {
    if (!canBeMoved || (GetParent() == parent))
        return;

    if (GetParent()) {
        OnUnload();
        GetParent()->RemoveChild(this);
    }

    this->parent = parent;

    if (parent) {
        parent->AddChild(this);
        OnLoad();
    }
}
void gle::Instance::ClearAllChildren() const {
    for (Instance *child : GetChildren()) {
        child->Destroy();
    }
}
void gle::Instance::SetActive(bool active) {
    if (this->active == active)
        return;
    this->active = active;
    OnActiveSet(active);
}
void gle::Instance::Rename(std::string newName) {
    if (!canBeRenamed)
        return;
    this->name = newName;
}

// Static methods
gle::Instance *gle::Instance::GetInstanceByID(size_t id) {
    if (allInstances.find(id) != allInstances.end()) {
        return allInstances[id];
    } else {
        return NULL;
    }
}
void gle::Instance::ClearAllInstances() {
    for (auto &[id, instance] : allInstances) {
        instance->Destroy();
    }
}

// Private methods
void gle::Instance::AddChild(gle::Instance *child) {
    if (std::find(children.begin(), children.end(), child) != children.end())
        return;
    children.push_back(child);
}
void gle::Instance::RemoveChild(gle::Instance *child) {
    auto it = std::find(children.begin(), children.end(), child);
    if (it == children.end())
        return;
    children.erase(it);
}