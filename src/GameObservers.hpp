#pragma once
#include "Updatable.hpp"
#include <vector>

class GameObservers {
public:
    void subscribeUpdate(Updatable* obj);
    void unsubscribeUpdate(Updatable* obj);

protected:
    void update(uint32_t deltaTime);

private:
    std::vector<Updatable*> updateSubscribers;
};
