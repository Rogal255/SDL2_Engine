#pragma once

template <typename T, typename... TArgs>
void EntityManager::addComponent(const EntityID& tEntityID, ComponentManager<T>& componentManager, TArgs&&... tArgs) {
    auto it = getEntityIterator(tEntityID);
    if (hasComponent<T>(it)) {
        return;
    }
    auto componentID = componentManager.addComponent(tEntityID, std::forward<TArgs>(tArgs)...);
    it->second.sparseArray[T::typeID] = componentID;
}

template <typename T>
void EntityManager::removeComponent(const EntityID& tEntityID, ComponentManager<T>& componentManager) {
    auto it = getEntityIterator(tEntityID);
    if (!hasComponent<T>(it)) {
        throw std::invalid_argument("EntityManager::removeComponent - Entity does not have provided Component");
    }
    std::vector<EntityID> invalidatedEntities = componentManager.removeComponent(getComponentID<T>(tEntityID));
    it->second.sparseArray[T::typeID] = ComponentID(0);
    for (const auto& entityID : invalidatedEntities) {
        it = getEntityIterator(entityID);
        it->second.sparseArray[T::typeID] += -1;
    }
}

template <typename T>
bool EntityManager::hasComponent(const EntityID& tEntityID) {
    auto it = getEntityIterator(tEntityID);
    return hasComponent<T>(it);
}

template <typename T>
inline bool EntityManager::hasComponent(const EntityIterator& tEntityIterator) {
    if (tEntityIterator->second.sparseArray[T::typeID]) {
        return true;
    }
    return false;
}

template <typename T>
T& EntityManager::getComponent(const EntityID& tEntityID, ComponentManager<T>& componentManager) {
    auto it = getEntityIterator(tEntityID);
    return getComponent<T>(it, componentManager);
}

template <typename T>
inline T& EntityManager::getComponent(const EntityIterator& tEntityIterator, ComponentManager<T>& componentManager) {
    return componentManager.getComponent(tEntityIterator->second.sparseArray[T::typeID]);
}

template <typename T>
ComponentID EntityManager::getComponentID(const EntityID& tEntityID) {
    auto it = getEntityIterator(tEntityID);
    return ComponentID(it->second.sparseArray[T::typeID]);
}