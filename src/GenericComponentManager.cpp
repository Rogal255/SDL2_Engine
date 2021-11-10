#include "GenericComponentManager.hpp"

GenericComponentManager::GenericComponentManager(ComponentEnum componentType) {
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

GenericComponentManager::~GenericComponentManager() {
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
