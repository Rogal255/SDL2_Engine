#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "Entity.hpp"
#include "HelperTypes.hpp"
#include <map>
#include <memory>

class EntityManager {
public:
    EntityID addEntity() {
        auto entityID = generateNextEntityID();
        data_.insert({entityID, Entity(entityID)});
        return entityID;
    }

    template <typename T>
    T& addComponent(const EntityID& tEntityID) {
        ComponentID componentID = ComponentManager<T>::addComponent(tEntityID);
        T& component = ComponentManager<T>::getComponent(componentID);
        data_.find(tEntityID)->second.sparseArray[T::typeID] = componentID;
        return component;
    }

    template <typename T>
    T& getComponent(const EntityID& tEntityID) {
        return ComponentManager<T>::getComponent(ComponentID(data_.find(tEntityID)->second.sparseArray[T::typeID]));
    }

    template <typename T>
    ComponentID getComponentID(const EntityID& tEntityID) {
        return ComponentID(data_.find(tEntityID)->second.sparseArray[T::typeID]);
    }

private:
    std::map<EntityID, Entity> data_;

    static EntityID generateNextEntityID() {
        static size_t lastAssigned {1u};
        return EntityID(lastAssigned++);
    }
};
