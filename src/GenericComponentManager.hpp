#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include <stdexcept>
#include <type_traits>

class GenericComponentManager {
public:
    explicit GenericComponentManager(ComponentEnum componentType);
    ~GenericComponentManager();

    template <typename T>
    bool checkType() const {
        return T::typeID == typeID_;
    }

    template <typename T>
    ComponentManager<T>& getManager() {
        if constexpr (std::is_same<T, TransformComponent>::value) {
            return transformComponentManager_;
        }
        if constexpr (std::is_same<T, SpriteComponent>::value) {
            return spriteComponentManager_;
        }
    }

private:
    ComponentEnum typeID_;

    union {
        ComponentManager<TransformComponent> transformComponentManager_;
        ComponentManager<SpriteComponent> spriteComponentManager_;
    };
};
