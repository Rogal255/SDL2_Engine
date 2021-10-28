#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "Entity.hpp"
#include "HelperTypes.hpp"
#include <cstdio>
#include <map>
#include <memory>

class EntityManager {
public:
    static EntityID addEntity() noexcept {
        auto entityID = generateNextEntityID();
        data_.insert({entityID, Entity(entityID)});
        return entityID;
    }

    template <typename T>
    static bool hasComponent(const EntityID& tEntityID) noexcept {
        if (data_.find(tEntityID)->second.sparseArray[T::typeID]) {
            return true;
        }
        return false;
    }

    template <typename T>
    static T& addComponent(const EntityID& tEntityID) noexcept {
        if (EntityManager::hasComponent<T>(tEntityID)) {
            return EntityManager::getComponent<T>(tEntityID);
        }
        ComponentID componentID = ComponentManager<T>::addComponent(tEntityID);
        T& component = ComponentManager<T>::getComponent(componentID);
        data_.find(tEntityID)->second.sparseArray[T::typeID] = componentID;
        return component;
    }

    template <typename T>
    static T& getComponent(const EntityID& tEntityID) {
        return ComponentManager<T>::getComponent(ComponentID(data_.find(tEntityID)->second.sparseArray[T::typeID]));
    }

    template <typename T>
    static ComponentID getComponentID(const EntityID& tEntityID) {
        return ComponentID(data_.find(tEntityID)->second.sparseArray[T::typeID]);
    }

    static void clear() { data_.clear(); }

private:
    static inline std::map<EntityID, Entity> data_;

    static EntityID generateNextEntityID() {
        static size_t lastAssigned {1u};
        return EntityID(lastAssigned++);
    }
};
