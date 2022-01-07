#pragma once
#include "ContentManager.hpp"
#include "HelperTypes.hpp"
#include <utility>

class Scene {
public:
    EntityID addEntity() noexcept;
    void removeEntity(const EntityID& tEntityID);
    void clear();

    template <typename T, typename... TArgs>
    void addComponent(const EntityID& tEntityID, TArgs&&... tArgs) {
        manager_.addComponent<T>(tEntityID, std::forward<TArgs>(tArgs)...);
    }

    template <typename T>
    void removeComponent(const EntityID& tEntityID) {
        return manager_.removeComponent<T>(tEntityID);
    }

    template <typename T>
    bool hasComponent(const EntityID& tEntityID) {
        return manager_.hasComponent<T>(tEntityID);
    }

    template <typename T>
    T& getComponent(const EntityID& tEntityID) {
        return manager_.getComponent<T>(tEntityID);
    }

    template <typename T>
    ComponentID getComponentID(const EntityID& tEntityID) {
        return manager_.getComponentID<T>(tEntityID);
    }

private:
    ContentManager manager_;
};
