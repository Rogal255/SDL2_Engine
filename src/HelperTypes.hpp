#pragma once
#include <stdio.h>

enum ComponentEnum { Transform, Sprite, Size };

struct EntityID {
    explicit constexpr EntityID(const size_t& ID) : value {ID} { }
    constexpr EntityID() = default;
    constexpr EntityID& operator=(const EntityID&) = default;
    constexpr bool operator==(const EntityID& other) const { return value == other.value; }
    constexpr bool operator<(const EntityID& other) const { return value < other.value; }
    size_t value {0};
};

struct ComponentID {
    explicit constexpr ComponentID(const size_t& ID) : value {ID} { }
    constexpr ComponentID() = default;
    constexpr ComponentID& operator=(const ComponentID&) = default;
    constexpr bool operator==(const ComponentID& other) const { return value == other.value; }
    constexpr bool operator<(const ComponentID& other) const { return value < other.value; }
    size_t value {0};
};
