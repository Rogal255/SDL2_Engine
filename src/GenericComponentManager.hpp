#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include <stdexcept>

class GenericComponentManager {
public:
    GenericComponentManager(ComponentEnum componentType) {
        typeID_ = componentType;
        switch (typeID_) {
        case Transform:
            new (&transformComponentManager_) ComponentManager<TransformComponent>;
            break;
        case Sprite:
            new (&spriteComponentManager_) ComponentManager<SpriteComponent>;
            break;
        default:
            throw std::invalid_argument("GenericComponentManager constructor - bad Component provided");
        }
    }

    ~GenericComponentManager() {
        switch (typeID_) {
        case Transform:
            transformComponentManager_.~ComponentManager<TransformComponent>();
            break;
        case Sprite:
            spriteComponentManager_.~ComponentManager<SpriteComponent>();
            break;
        default:
            break;
        }
    }

    template <typename T>
    bool checkType() const {
        return T::typeID == typeID_;
    }

    template <typename T>
    ComponentManager<T>* getManager();

    template <>
    ComponentManager<TransformComponent>* getManager() {
        return &transformComponentManager_;
    }

    template <>
    ComponentManager<SpriteComponent>* getManager() {
        return &spriteComponentManager_;
    }

private:
    ComponentEnum typeID_;

    union {
        ComponentManager<TransformComponent> transformComponentManager_;
        ComponentManager<SpriteComponent> spriteComponentManager_;
    };
};
