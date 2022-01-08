#pragma once
#include "HelperTypes.hpp"

struct Component {
    explicit constexpr Component(const EntityID& tEntityID) : entityID {tEntityID} { }
    EntityID entityID;
};

struct TransformComponent : public Component {
    explicit constexpr TransformComponent(const EntityID& tEntityID) : Component(tEntityID) { }
    constexpr static ComponentEnum typeID {ComponentEnum::Transform};
    float scale {1.f};
    float posX {0.f};
    float posY {0.f};
    float speedX {0.f};
    float speedY {0.f};
    float rotation {0.f};
    float speedRotation {0.f};

};

struct SpriteComponent : public Component {
    explicit constexpr SpriteComponent(const EntityID& tEntityID) : Component(tEntityID) { }
    constexpr static ComponentEnum typeID {ComponentEnum::Sprite};
    float posX {0.f};
    float posY {0.f};
};
