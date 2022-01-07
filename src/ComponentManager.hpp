#pragma once
#include "HelperTypes.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

class Scene;

template <class T>
class ComponentManager {
public:
    ComponentManager() { data_.reserve(10); }

    std::vector<EntityID> removeComponent(const ComponentID& componentID) {
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

    T& getComponent(const ComponentID& componentID) {
        if (componentID.value >= data_.size()) {
            throw std::invalid_argument("ComponentManager::getComponentManager() - provided ComponentID out of range");
        }
        return data_[componentID.value];
    }

    void clear() {
        data_.clear();
        data_.emplace_back(EntityID(0));
    }

    template <typename... TArgs>
    ComponentID addComponent(const EntityID& tEntityID, TArgs&&... tArgs) {
        data_.emplace_back(tEntityID, std::forward<TArgs>(tArgs)...);
        return ComponentID(data_.size() - 1);
    }

private:
    ComponentEnum typeID {T::typeID};
    std::vector<T> data_ {T(EntityID(0))};
};
