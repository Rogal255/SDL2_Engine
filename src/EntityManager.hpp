#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "Entity.hpp"
#include "HelperTypes.hpp"
#include <cstdio>
#include <map>
#include <memory>
#include <stdexcept>

class EntityManager {
public:
    using EntityIterator = std::map<EntityID, Entity>::iterator;
    friend class Scene;

    std::map<EntityID, Entity> data_;

    EntityID addEntity() noexcept {
        auto entityID = generateNextEntityID();
        data_.insert({entityID, Entity(entityID)});
        return entityID;
    }

    template <typename T>
    T& addComponent(const EntityID& tEntityID, ComponentManager<T>& componentManager) {
        auto it = getEntityIterator(tEntityID);
        if (hasComponent<T>(it)) {
            return getComponent<T>(it, componentManager);
        }
        auto componentID = componentManager.addComponent(tEntityID);
        it->second.sparseArray[T::typeID] = componentID;
        return componentManager.getComponent(componentID);
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
        if (tEntityIterator->second.sparseArray[T::typeID]) {
            return true;
        }
        return false;
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

    void clear() noexcept { data_.clear(); }

    inline EntityID generateNextEntityID() noexcept { // NOLINT(readability-convert-member-functions-to-static)
        static size_t lastAssigned {1u};
        return EntityID(lastAssigned++);
    }

    inline EntityIterator getEntityIterator(const EntityID& tEntityID) {
        auto it = data_.find(tEntityID);
        if (it == data_.end()) {
            throw std::invalid_argument("EntityManager::removeComponent - no Entity of given EntityID");
        }
        return it;
    }
};
