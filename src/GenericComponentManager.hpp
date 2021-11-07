#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include <stdexcept>

class GenericComponentManager {
public:
    GenericComponentManager(const ComponentEnum& componentType) {
        typeID = componentType;
        switch (typeID) {
        case Transform:
            new (&transformComponentManager) ComponentManager<TransformComponent>;
            break;
        case Sprite:
            new (&spriteComponentManager) ComponentManager<SpriteComponent>;
            break;
        default:
            throw std::invalid_argument("GenericComponentManager constructor - bad Component provided");
        }
    }

    ~GenericComponentManager() {
        switch (typeID) {
        case Transform:
            transformComponentManager.~ComponentManager<TransformComponent>();
            break;
        case Sprite:
            spriteComponentManager.~ComponentManager<SpriteComponent>();
            break;
        default:
            break;
        }
    }

    ComponentEnum typeID;

    template <typename T>
    bool checkType() const {
        return T::typeID == typeID;
    }

    union {
        ComponentManager<TransformComponent> transformComponentManager;
        ComponentManager<SpriteComponent> spriteComponentManager;
    };

    template <typename T>
    ComponentManager<T>* getManager();

    template <>
    ComponentManager<TransformComponent>* getManager() {
        return &transformComponentManager;
    }

    template <>
    ComponentManager<SpriteComponent>* getManager() {
        return &spriteComponentManager;
    }
};
