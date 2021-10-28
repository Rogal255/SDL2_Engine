#pragma once
#include "Component.hpp"
#include "HelperTypes.hpp"
#include <array>

class EntityManager;

class Entity {
    friend EntityManager;

public:
    EntityID entityID;
    std::array<ComponentID, ComponentEnum::Size> sparseArray {ComponentID(0)};

private:
    explicit constexpr Entity(const EntityID& tEntityID) noexcept : entityID {tEntityID} { }
};
