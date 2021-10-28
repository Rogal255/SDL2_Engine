#pragma once
#include "HelperTypes.hpp"
#include "SDL.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

template <class T>
class ComponentManager {
public:
    static ComponentID addComponent(const EntityID& tEntityID) noexcept {
        data_.emplace_back(tEntityID);
        return ComponentID(data_.size() - 1);
    }

    // void removeComponent(const size_t index) { data_.erase(data_.begin() + index); }

    static T& getComponent(const ComponentID& componentID) {
        if (componentID.value >= data_.size()) {
            throw std::range_error("ComponentManager::getComponent() - provided ComponentID out of range");
        }
        return data_[componentID.value];
    }

    static void clear(){
        data_.clear();
        data_.emplace_back(EntityID(0));
    }

private:
    static inline std::vector<T> data_ {T(EntityID(0))};
};
