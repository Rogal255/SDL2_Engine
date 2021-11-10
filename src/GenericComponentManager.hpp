#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include <stdexcept>

class GenericComponentManager {
public:
    explicit GenericComponentManager(ComponentEnum componentType);
    ~GenericComponentManager();

    template <typename T>
    bool checkType() const;

    template <typename T>
    ComponentManager<T>& getManager();
    template <>
    ComponentManager<TransformComponent>& getManager();
    template <>
    ComponentManager<SpriteComponent>& getManager();

private:
    ComponentEnum typeID_;

    union {
        ComponentManager<TransformComponent> transformComponentManager_;
        ComponentManager<SpriteComponent> spriteComponentManager_;
    };
};

#include "GenericComponentManager.tpp"
