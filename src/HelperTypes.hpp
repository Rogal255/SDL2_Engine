#pragma once
#include <cstdio>

enum ComponentEnum { Transform, Sprite, Size };

struct EntityID {
    explicit constexpr EntityID(const size_t& ID) noexcept : value {ID} { }
    constexpr EntityID() = default;
    constexpr EntityID& operator=(const EntityID&) = default;
    constexpr bool operator==(const EntityID& other) const noexcept { return value == other.value; }
    constexpr bool operator<(const EntityID& other) const noexcept { return value < other.value; }
    size_t value {0};
};

struct ComponentID {
    explicit constexpr ComponentID(const size_t& ID) noexcept : value {ID} { }
    constexpr ComponentID() = default;
    constexpr ComponentID& operator=(const ComponentID&) = default;
    constexpr bool operator==(const ComponentID& other) const noexcept { return value == other.value; }
    constexpr bool operator<(const ComponentID& other) const noexcept { return value < other.value; }

    constexpr ComponentID& operator-=(unsigned short i) noexcept {
        value -= i;
        return *this;
    }

    size_t value {0};
};
