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

    std::array<GenericComponentManager, ComponentEnum::Size> managersArray_ {
        GenericComponentManager(ComponentEnum::Transform),
        GenericComponentManager(ComponentEnum::Sprite),
    };

    template <typename T>
    ComponentManager<T>& getComponentManager();
};

#include "Scene.tpp"
