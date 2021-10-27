#pragma once
#include "Component.hpp"
#include "HelperTypes.hpp"
#include <array>

class EntityManager;

class Entity {
    friend EntityManager;

public:
    EntityID entityID;
    std::array<size_t, ComponentEnum::Size> sparseArray {0};

private:
    explicit constexpr Entity(const EntityID& tEntityID) : entityID {tEntityID} { }
};
