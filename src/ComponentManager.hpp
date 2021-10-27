#pragma once
#include "HelperTypes.hpp"
#include <algorithm>
#include <vector>

template <class T>
class ComponentManager {
public:
    static ComponentID addComponent(const EntityID& tEntityID) {
        data_.emplace_back(tEntityID);
        return ComponentID(data_.size() - 1);
    }

    // void removeComponent(const size_t index) { data_.erase(data_.begin() + index); }

    static T& getComponent(const ComponentID& componentID) { return data_[componentID.value]; }

private:
    static inline std::vector<T> data_ {};
};
