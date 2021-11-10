#include "EntityManager.hpp"

EntityID EntityManager::addEntity() {
    auto entityID = generateNextEntityID();
    data_.insert({entityID, Entity(entityID)});
    return entityID;
}

void EntityManager::removeEntity(const EntityID& tEntityID) {
    auto it = getEntityIterator(tEntityID);
    data_.erase(it);
}

void EntityManager::clear() noexcept { data_.clear(); }

EntityID EntityManager::generateNextEntityID() noexcept {
    static size_t lastAssigned {1u};
    return EntityID(lastAssigned++);
}

EntityIterator EntityManager::getEntityIterator(const EntityID& tEntityID) {
    auto it = data_.find(tEntityID);
    if (it == data_.end()) {
        throw std::invalid_argument("EntityManager::removeComponent - no Entity of given EntityID");
    }
    return it;
}
