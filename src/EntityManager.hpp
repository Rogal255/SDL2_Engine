#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "Entity.hpp"
#include "HelperTypes.hpp"
#include <cstdio>
#include <map>
#include <memory>
#include <stdexcept>
#include <utility>

class Scene;
using EntityIterator = std::map<EntityID, Entity>::iterator;

class EntityManager {
    friend class Scene;

    EntityID addEntity();
    void removeEntity(const EntityID& tEntityID);
    void clear() noexcept;
    EntityID generateNextEntityID() noexcept;
    EntityIterator getEntityIterator(const EntityID& tEntityID);
    std::map<EntityID, Entity> data_;

    template <typename T, typename... TArgs>
    void addComponent(const EntityID& tEntityID, ComponentManager<T>& componentManager, TArgs&&... tArgs) {
        auto it = getEntityIterator(tEntityID);
        if (hasComponent<T>(it)) {
            return;
        }
        auto componentID = componentManager.addComponent(tEntityID, std::forward<TArgs>(tArgs)...);
        it->second.sparseArray[T::typeID] = componentID;
    }

    template <typename T>
    void removeComponent(const EntityID& tEntityID, ComponentManager<T>& componentManager) {
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
    bool hasComponent(const EntityID& tEntityID) {
        auto it = getEntityIterator(tEntityID);
        return hasComponent<T>(it);
    }

    template <typename T>
    inline bool hasComponent(const EntityIterator& tEntityIterator) {
        return static_cast<bool>(tEntityIterator->second.sparseArray[T::typeID]);
    }

    template <typename T>
    T& getComponent(const EntityID& tEntityID, ComponentManager<T>& componentManager) {
        auto it = getEntityIterator(tEntityID);
        return getComponent<T>(it, componentManager);
    }

    template <typename T>
    inline T& getComponent(const EntityIterator& tEntityIterator, ComponentManager<T>& componentManager) {
        return componentManager.getComponent(tEntityIterator->second.sparseArray[T::typeID]);
    }

    template <typename T>
    ComponentID getComponentID(const EntityID& tEntityID) {
        auto it = getEntityIterator(tEntityID);
        return ComponentID(it->second.sparseArray[T::typeID]);
    }
};
