#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "HelperTypes.hpp"
#include <type_traits>

class Scene {
public:
    EntityID addEntity() noexcept { return entityManager.addEntity(); }

    template <typename T>
    T& addComponent(const EntityID& tEntityID) {
        return entityManager.addComponent(tEntityID, getComponentManager<T>());
    }

    template <typename T>
    void removeComponent(const EntityID& tEntityID) {
        return entityManager.removeComponent(tEntityID, getComponentManager<T>());
    }

    template <typename T>
    bool hasComponent(const EntityID& tEntityID) {
        return entityManager.hasComponent<T>(tEntityID);
    }

    template <typename T>
    T& getComponent(const EntityID& tEntityID) {
        return entityManager.getComponent<T>(tEntityID, getComponentManager<T>());
    }

    template <typename T>
    ComponentID getComponentID(const EntityID& tEntityID) {
        return entityManager.getComponentID<T>(tEntityID);
    }

    void clear() {
        entityManager.clear();
        transformComponentManager.clear();
    }

private:
    EntityManager entityManager {EntityManager()};
    ComponentManager<TransformComponent> transformComponentManager {ComponentManager<TransformComponent>()};

    template <typename T>
    ComponentManager<T>& getComponentManager() {
        if (std::is_same<T, TransformComponent>::value) {
            return transformComponentManager;
        }
    }
};
