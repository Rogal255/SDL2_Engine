#pragma once

template <class T>
ComponentManager<T>::ComponentManager() { data_.reserve(10); }

template <class T>
std::vector<EntityID> ComponentManager<T>::removeComponent(const ComponentID& componentID) {
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

template <class T>
T& ComponentManager<T>::getComponent(const ComponentID& componentID) {
    if (componentID.value >= data_.size()) {
        throw std::invalid_argument("ComponentManager::getComponentManager() - provided ComponentID out of range");
    }
    return data_[componentID.value];
}

template <class T>
void ComponentManager<T>::clear() {
    data_.clear();
    data_.emplace_back(EntityID(0));
}

template <class T>
template <typename... TArgs>
ComponentID ComponentManager<T>::addComponent(const EntityID& tEntityID, TArgs&&... tArgs) {
    data_.emplace_back(tEntityID, std::forward<TArgs>(tArgs)...);
    return ComponentID(data_.size() - 1);
}
