#include "ContentManager.hpp"

void ContentManager::setUpdateManager(GameObservers* ptr) { gameObservers_ = ptr; }

EntityID ContentManager::addEntity() {
    auto entityID = generateNextEntityID();
    entities_.insert({entityID, Entity(entityID)});
    return entityID;
}

void ContentManager::removeEntity(const EntityID& tEntityID) {
    auto it = getEntityIterator(tEntityID);
    if (hasComponent<TransformComponent>(tEntityID)) {
        removeComponent<TransformComponent>(tEntityID);
    }
    if (hasComponent<SpriteComponent>(tEntityID)) {
        removeComponent<SpriteComponent>(tEntityID);
    }
    entities_.erase(it);
}

void ContentManager::clear() noexcept {
    entities_.clear();
    getComponentManager<TransformComponent>().clear();
    getComponentManager<SpriteComponent>().clear();
}

EntityID ContentManager::generateNextEntityID() noexcept {
    static size_t lastAssigned {1u};
    return EntityID(lastAssigned++);
}

ContentManager::EntityIterator ContentManager::getEntityIterator(const EntityID& tEntityID) {
    auto it = entities_.find(tEntityID);
    if (it == entities_.end()) {
        throw std::invalid_argument("ContentManager::removeComponent - no Entity of given EntityID");
    }
    return it;
}
