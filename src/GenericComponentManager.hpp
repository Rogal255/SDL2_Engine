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
            data_.transformComponentManager = ComponentManager<TransformComponent>();
            break;
        case Sprite:
            data_.spriteComponentManager = ComponentManager<SpriteComponent>();
            break;
        default:
            throw std::invalid_argument("GenericComponentManager constructor - bad Component provided");
        }
    }

    ComponentEnum typeID;

    template <typename T>
    bool checkType() const {
        return T::typeID == typeID;
    }

    union Components {
        Components() { memset(this, 0, sizeof(*this)); };
        ~Components() {};
        ComponentManager<TransformComponent> transformComponentManager;
        ComponentManager<SpriteComponent> spriteComponentManager;
    };

    ComponentManager<TransformComponent>* getManager() { return &data_.transformComponentManager; }

    Components data_ {};
};
