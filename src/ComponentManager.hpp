#pragma once
#include "HelperTypes.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

class Scene;

template <class T>
class ComponentManager {
public:
    ComponentManager();
    std::vector<EntityID> removeComponent(const ComponentID& componentID);
    T& getComponent(const ComponentID& componentID);
    void clear();

    template <typename... TArgs>
    ComponentID addComponent(const EntityID& tEntityID, TArgs&&... tArgs);

private:
    ComponentEnum typeID {T::typeID};
    std::vector<T> data_ {T(EntityID(0))};
};

#include "ComponentManager.tpp"
