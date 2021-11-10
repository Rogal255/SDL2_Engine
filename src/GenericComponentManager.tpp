#pragma once

template <typename T>
bool GenericComponentManager::checkType() const {
    return T::typeID == typeID_;
}

template <>
ComponentManager<TransformComponent>& GenericComponentManager::getManager() {
    return transformComponentManager_;
}

template <>
ComponentManager<SpriteComponent>& GenericComponentManager::getManager() {
    return spriteComponentManager_;
}
