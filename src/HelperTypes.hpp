#pragma once

enum ComponentEnum { Transform, Sprite, Size };

struct EntityID {
    explicit constexpr EntityID(const size_t& ID) : value {ID} { }
    constexpr EntityID() = default;
    constexpr EntityID& operator=(const EntityID&) = default;
    constexpr bool operator==(const EntityID& other) const { return value == other.value; }
    constexpr bool operator<(const EntityID& other) const { return value < other.value; }
    size_t value {0};
};
