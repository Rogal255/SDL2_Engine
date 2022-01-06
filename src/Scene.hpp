#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "HelperTypes.hpp"
#include "SDL.h"
#include <array>
#include <variant>

using ComponentManagerVariant = std::variant<ComponentManager<TransformComponent>, ComponentManager<SpriteComponent>>;

class Scene {
public:
    EntityID addEntity() noexcept;
    void removeEntity(const EntityID& tEntityID);
    void clear();

    template <typename T>
    void addComponent(const EntityID& tEntityID);

    template <typename T>
    void removeComponent(const EntityID& tEntityID);

    template <typename T>
    bool hasComponent(const EntityID& tEntityID);

    template <typename T>
    T& getComponent(const EntityID& tEntityID);

    template <typename T>
    ComponentID getComponentID(const EntityID& tEntityID);

private:
    EntityManager entityManager {EntityManager()};

    std::array<ComponentManagerVariant, ComponentEnum::Size> managersArray_ {
        ComponentManager<TransformComponent>(),
        ComponentManager<SpriteComponent>(),
    };

    template <typename T>
    ComponentManager<T>& getComponentManager();
};

#include "Scene.tpp"
