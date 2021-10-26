#pragma once
#include <array>
#include "Component.hpp"

class EntityManager;

class Entity {
    friend EntityManager;

public:
    Entity() = default;
    size_t ID;
    std::array<size_t, ComponentID::Size> sparseArray {0};

private:
    explicit Entity(size_t tID) : ID {tID} { }
};
