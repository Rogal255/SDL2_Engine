#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "Entity.hpp"
#include <map>
#include <memory>

class EntityManager {
public:
    size_t addEntity() noexcept {
        auto id = generateNextEntityID();
        data_[id] = Entity(id);
        return id;
    }

    template <typename T>
    T& addComponent(size_t tEntityIndex) {
        size_t componentIndex = ComponentManager<T>::addComponent();
        T& component = ComponentManager<T>::getComponent(componentIndex);
        component.entityID = tEntityIndex;
        data_[tEntityIndex].sparseArray[T::typeID] = componentIndex;
        return component;
    }

    template <typename T>
    T& getComponent(size_t tEntityIndex) {
        return ComponentManager<T>::getComponent(data_[tEntityIndex].sparseArray[T::typeID]);
    }

private:
    std::map<size_t, Entity> data_;

    static size_t generateNextEntityID() {
        static size_t lastAssigned {1u};
        return lastAssigned++;
    }
};
