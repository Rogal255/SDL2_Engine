#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "GenericComponentManager.hpp"
#include "HelperTypes.hpp"
#include "SDL.h"
#include <array>

class Scene {
public:
    EntityID addEntity() noexcept { return entityManager.addEntity(); }

    void removeEntity(const EntityID& tEntityID) {
        if (hasComponent<TransformComponent>(tEntityID)) {
            removeComponent<TransformComponent>(tEntityID);
        }
        entityManager.removeEntity(tEntityID);
    }

    template <typename T>
    void addComponent(const EntityID& tEntityID) {
        entityManager.addComponent(tEntityID, getComponentManager<T>());
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
        getComponentManager<TransformComponent>().clear();
        getComponentManager<SpriteComponent>().clear();
    }

private:
    EntityManager entityManager {EntityManager()};

    std::array<GenericComponentManager, ComponentEnum::Size> managersArray_ {
        GenericComponentManager(ComponentEnum::Transform),
        GenericComponentManager(ComponentEnum::Sprite),
    };

    template <typename T>
    ComponentManager<T>& getComponentManager() {
        for (auto& manager : managersArray_) {
            if (manager.checkType<T>()) {
                return *(manager.getManager<T>());
            }
        }
        throw std::invalid_argument("Manager does not exist");
    }
};
