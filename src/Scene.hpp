#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "HelperTypes.hpp"
#include "SDL.h"
#include <array>
#include <type_traits>
#include <variant>

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
    T& addComponent(const EntityID& tEntityID) {
        return entityManager.addComponent(tEntityID, std::get<ComponentManager<T>>(getComponentManager<T>()));
    }

    template <typename T>
    void removeComponent(const EntityID& tEntityID) {
        return entityManager.removeComponent(tEntityID, std::get<ComponentManager<T>>(getComponentManager<T>()));
    }

    template <typename T>
    bool hasComponent(const EntityID& tEntityID) {
        return entityManager.hasComponent<T>(tEntityID);
    }

    template <typename T>
    T& getComponent(const EntityID& tEntityID) {
        return entityManager.getComponent<T>(tEntityID, std::get<ComponentManager<T>>(getComponentManager<T>()));
    }

    template <typename T>
    ComponentID getComponentID(const EntityID& tEntityID) {
        return entityManager.getComponentID<T>(tEntityID);
    }

    void clear() {
        entityManager.clear();
        std::get<ComponentManager<TransformComponent>>(managersArray_[0]).clear();
        std::get<ComponentManager<SpriteComponent>>(managersArray_[1]).clear();
    }

private:
    EntityManager entityManager {EntityManager()};

    using ComponentManagerVariant
        = std::variant<ComponentManager<TransformComponent>, ComponentManager<SpriteComponent>>;

    std::array<ComponentManagerVariant, ComponentEnum::Size> managersArray_ {
        ComponentManagerVariant(ComponentManager<TransformComponent>()),
        ComponentManagerVariant(ComponentManager<SpriteComponent>())};

    template <typename T>
    ComponentManagerVariant& getComponentManager() {
        for (auto& variant : managersArray_) {
            if (std::holds_alternative<ComponentManager<T>>(variant)) {
                return variant;
            }
        }
        throw std::invalid_argument("Manager does not exist");
    }
};
