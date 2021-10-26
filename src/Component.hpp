#pragma once

enum ComponentID {
    Transform,
    Sprite,
    Size
};

struct Component {
    size_t entityID {0};
};

struct TransformComponent : public Component{
    constexpr static ComponentID typeID {ComponentID::Transform};
    float posX {0.f};
    float posY {0.f};
};

// TODO: Add sprite component
