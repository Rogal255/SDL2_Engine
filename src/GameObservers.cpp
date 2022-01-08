#include "GameObservers.hpp"

void GameObservers::subscribeUpdate(Updatable* obj) {
    if (std::find(updateSubscribers.cbegin(), updateSubscribers.cend(), obj) == updateSubscribers.cend()) {
        updateSubscribers.push_back(obj);
    }
}

void GameObservers::unsubscribeUpdate(Updatable* obj) {
    auto it = std::find(updateSubscribers.cbegin(), updateSubscribers.cend(), obj);
    if (it != updateSubscribers.cend()) {
        updateSubscribers.erase(it);
    }
}

void GameObservers::update(uint32_t deltaTime) {
    for (auto updatableObj : updateSubscribers) {
        updatableObj->update(deltaTime);
    }
}
