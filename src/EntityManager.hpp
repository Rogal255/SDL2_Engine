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
    static EntityID addEntity() noexcept {
        auto entityID = generateNextEntityID();
        data_.insert({entityID, Entity(entityID)});
        return entityID;
    }

    template <typename T>
    static T& addComponent(const EntityID& tEntityID) {
        auto it = getEntityIterator(tEntityID);
        if (EntityManager::hasComponent<T>(tEntityID)) {
            return EntityManager::getComponent<T>(tEntityID);
        }
        auto componentID = ComponentManager<T>::addComponent(tEntityID);
        it->second.sparseArray[T::typeID] = componentID;
        return ComponentManager<T>::getComponent(componentID);
    }

    template <typename T>
    static void removeComponent(const EntityID& tEntityID) {
        auto it = getEntityIterator(tEntityID);
        if (!EntityManager::hasComponent<T>(tEntityID)) {
            throw std::invalid_argument("EntityManager::removeComponent - Entity does not have provided Component");
        }
        std::vector<EntityID> invalidatedEntities = ComponentManager<T>::removeComponent(getComponentID<T>(tEntityID));
        it->second.sparseArray[T::typeID] = ComponentID(0);
        for (const auto& entityID : invalidatedEntities) {
            it = getEntityIterator(entityID);
            it->second.sparseArray[T::typeID] += -1;
        }
    }

    template <typename T>
    static bool hasComponent(const EntityID& tEntityID) {
        auto it = getEntityIterator(tEntityID);
        if (it->second.sparseArray[T::typeID]) {
            return true;
        }
        return false;
    }

    template <typename T>
    static T& getComponent(const EntityID& tEntityID) {
        auto it = getEntityIterator(tEntityID);
        return ComponentManager<T>::getComponent(ComponentID(it->second.sparseArray[T::typeID]));
    }

    template <typename T>
    static ComponentID getComponentID(const EntityID& tEntityID) {
        auto it = getEntityIterator(tEntityID);
        return ComponentID(it->second.sparseArray[T::typeID]);
    }

    static void clear() noexcept { data_.clear(); }

private:
    static inline std::map<EntityID, Entity> data_;

    static EntityID generateNextEntityID() noexcept {
        static size_t lastAssigned {1u};
        return EntityID(lastAssigned++);
    }

    static std::map<EntityID, Entity>::iterator getEntityIterator(const EntityID& tEntityID) {
        auto it = data_.find(tEntityID);
        if (it == data_.end()) {
            throw std::invalid_argument("EntityManager::removeComponent - no Entity of given EntityID");
        }
        return it;
    };
};
