#pragma once
#include "HelperTypes.hpp"

struct Component {
    explicit constexpr Component(const EntityID& tEntityID) : entityID {tEntityID} { }
    EntityID entityID;
};

struct TransformComponent : public Component {
    explicit constexpr TransformComponent(const EntityID& tEntityID) : Component(tEntityID) { }
    constexpr static ComponentEnum typeID {ComponentEnum::Transform};
    float posX {0.f};
    float posY {0.f};
};

// TODO: Add sprite component
