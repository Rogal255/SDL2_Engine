#pragma once
#include "HelperTypes.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>

template <class T>
class ComponentManager {
public:
    static ComponentID addComponent(const EntityID& tEntityID) noexcept {
        data_.emplace_back(tEntityID);
        return ComponentID(data_.size() - 1);
    }

    static std::vector<EntityID> removeComponent(const ComponentID& componentID) {
        if (componentID.value >= data_.size()) {
            throw std::invalid_argument("ComponentManager::removeComponent() - provided ComponentID out of range");
        }
        data_.erase(data_.begin() + componentID.value);
        std::vector<EntityID> invalidatedEntities;
        invalidatedEntities.reserve(std::distance(data_.cbegin() + componentID.value, data_.cend()));
        std::transform(data_.begin() + componentID.value,
                       data_.end(),
                       std::back_inserter(invalidatedEntities),
                       [](const T& component) { return component.entityID; });
        return invalidatedEntities;
    }

    static T& getComponent(const ComponentID& componentID) {
        if (componentID.value >= data_.size()) {
            throw std::invalid_argument("ComponentManager::getComponent() - provided ComponentID out of range");
        }
        return data_[componentID.value];
    }

    static void clear() {
        data_.clear();
        data_.emplace_back(EntityID(0));
    }

private:
    static inline std::vector<T> data_ {T(EntityID(0))};
};
