#pragma once

template <typename T>
void Scene::addComponent(const EntityID& tEntityID) {
    entityManager.addComponent(tEntityID, getComponentManager<T>());
}

template <typename T>
void Scene::removeComponent(const EntityID& tEntityID) {
    return entityManager.removeComponent(tEntityID, getComponentManager<T>());
}

template <typename T>
bool Scene::hasComponent(const EntityID& tEntityID) {
    return entityManager.hasComponent<T>(tEntityID);
}

template <typename T>
T& Scene::getComponent(const EntityID& tEntityID) {
    return entityManager.getComponent<T>(tEntityID, getComponentManager<T>());
}
template <typename T>
ComponentID Scene::getComponentID(const EntityID& tEntityID) {
    return entityManager.getComponentID<T>(tEntityID);
}

template <typename T>
constexpr ComponentManager<T>& Scene::getComponentManager() {
    for (auto& managerVariant : managersArray_) {
        if (auto ptr = std::get_if<ComponentManager<T>>(&managerVariant)) {
            return *ptr;
        }
    }
    throw std::invalid_argument("Manager does not exist");
}
