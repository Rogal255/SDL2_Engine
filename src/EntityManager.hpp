#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "Entity.hpp"
#include "HelperTypes.hpp"
#include <cstdio>
#include <map>
#include <memory>
#include <stdexcept>
#include <utility>

class Scene;
using EntityIterator = std::map<EntityID, Entity>::iterator;

class EntityManager {
    friend class Scene;

    EntityID addEntity();
    void removeEntity(const EntityID& tEntityID);
    void clear() noexcept;
    EntityID generateNextEntityID() noexcept;
    EntityIterator getEntityIterator(const EntityID& tEntityID);
    std::map<EntityID, Entity> data_;

    template <typename T, typename... TArgs>
    void addComponent(const EntityID& tEntityID, ComponentManager<T>& componentManager, TArgs&&... tArgs);

    template <typename T>
    void removeComponent(const EntityID& tEntityID, ComponentManager<T>& componentManager);

    template <typename T>
    bool hasComponent(const EntityID& tEntityID);

    template <typename T>
    inline bool hasComponent(const EntityIterator& tEntityIterator);

    template <typename T>
    T& getComponent(const EntityID& tEntityID, ComponentManager<T>& componentManager);

    template <typename T>
    inline T& getComponent(const EntityIterator& tEntityIterator, ComponentManager<T>& componentManager);

    template <typename T>
    ComponentID getComponentID(const EntityID& tEntityID);
};

#include "EntityManager.tpp"
