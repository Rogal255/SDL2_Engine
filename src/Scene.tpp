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
ComponentManager<T>& Scene::getComponentManager() {
    for (auto& manager : managersArray_) {
        if (manager.checkType<T>()) {
            return manager.getManager<T>();
        }
    }
    throw std::invalid_argument("Manager does not exist");
}
