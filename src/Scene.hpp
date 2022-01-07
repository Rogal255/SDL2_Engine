#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "HelperTypes.hpp"
#include "SDL.h"
#include <array>
#include <variant>

class Scene {
    using ComponentManagerVariant
        = std::variant<ComponentManager<TransformComponent>, ComponentManager<SpriteComponent>>;

public:
    EntityID addEntity() noexcept;
    void removeEntity(const EntityID& tEntityID);
    void clear();

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

private:
    EntityManager entityManager {EntityManager()};

    std::array<ComponentManagerVariant, ComponentEnum::Size> managersArray_ {
        ComponentManager<TransformComponent>(),
        ComponentManager<SpriteComponent>(),
    };

    template <typename T>
    ComponentManager<T>& getComponentManager() {
        for (auto& managerVariant : managersArray_) {
            if (auto ptr = std::get_if<ComponentManager<T>>(&managerVariant)) {
                return *ptr;
            }
        }
        throw std::invalid_argument("Manager does not exist");
    }
};
