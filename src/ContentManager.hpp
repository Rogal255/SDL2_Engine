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
#include <variant>

class ContentManager {
    using EntityIterator = std::map<EntityID, Entity>::iterator;
    using ComponentManagerVariant
        = std::variant<ComponentManager<TransformComponent>, ComponentManager<SpriteComponent>>;

public:
    EntityID addEntity();
    void removeEntity(const EntityID& tEntityID);
    void clear() noexcept;
    EntityID generateNextEntityID() noexcept;
    EntityIterator getEntityIterator(const EntityID& tEntityID);

    template <typename T, typename... TArgs>
    void addComponent(const EntityID& tEntityID, TArgs&&... tArgs) {
        auto it = getEntityIterator(tEntityID);
        if (hasComponent<T>(it)) {
            return;
        }
        auto componentID = getComponentManager<T>().addComponent(tEntityID, std::forward<TArgs>(tArgs)...);
        it->second.sparseArray[T::typeID] = componentID;
    }

    template <typename T>
    void removeComponent(const EntityID& tEntityID) {
        auto it = getEntityIterator(tEntityID);
        if (!hasComponent<T>(it)) {
            throw std::invalid_argument("ContentManager::removeComponent - Entity does not have provided Component");
        }
        std::vector<EntityID> invalidatedEntities
            = getComponentManager<T>().removeComponent(getComponentID<T>(tEntityID));
        it->second.sparseArray[T::typeID] = ComponentID(0);
        for (const auto& entityID : invalidatedEntities) {
            it = getEntityIterator(entityID);
            it->second.sparseArray[T::typeID] += -1;
        }
    }

    template <typename T>
    bool hasComponent(const EntityID& tEntityID) {
        auto it = getEntityIterator(tEntityID);
        return hasComponent<T>(it);
    }

    template <typename T>
    inline bool hasComponent(const EntityIterator& tEntityIterator) {
        return static_cast<bool>(tEntityIterator->second.sparseArray[T::typeID]);
    }

    template <typename T>
    T& getComponent(const EntityID& tEntityID) {
        auto it = getEntityIterator(tEntityID);
        return getComponent<T>(it);
    }

    template <typename T>
    inline T& getComponent(const EntityIterator& tEntityIterator) {
        return getComponentManager<T>().getComponent(tEntityIterator->second.sparseArray[T::typeID]);
    }

    template <typename T>
    ComponentID getComponentID(const EntityID& tEntityID) {
        auto it = getEntityIterator(tEntityID);
        return ComponentID(it->second.sparseArray[T::typeID]);
    }

private:
    template <typename T>
    ComponentManager<T>& getComponentManager() {
        for (auto& managerVariant : managersArray_) {
            if (auto ptr = std::get_if<ComponentManager<T>>(&managerVariant)) {
                return *ptr;
            }
        }
        throw std::invalid_argument("Manager does not exist");
    }

    std::map<EntityID, Entity> entities_;

    std::array<ComponentManagerVariant, ComponentEnum::Size> managersArray_ {
        ComponentManager<TransformComponent>(),
        ComponentManager<SpriteComponent>(),
    };
};
