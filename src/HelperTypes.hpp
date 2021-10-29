#pragma once
#include <compare>
#include <cstdio>

enum ComponentEnum { Transform, Sprite, Size };

struct GenericID {
    explicit constexpr GenericID(const size_t& ID) noexcept : value {ID} { }
    constexpr GenericID() = default;
    constexpr GenericID& operator=(const GenericID&) = default;
    constexpr bool operator==(const GenericID& other) const noexcept { return value == other.value; }
    constexpr bool operator<(const GenericID& other) const noexcept { return value < other.value; }
    explicit constexpr operator bool() const { return value != 0; }
    size_t value {0};
};

struct EntityID : public GenericID {
    explicit constexpr EntityID(const size_t& ID) noexcept : GenericID(ID) { }
    constexpr EntityID() = default;
};

struct ComponentID : public GenericID {
    explicit constexpr ComponentID(const size_t& ID) noexcept : GenericID(ID) { }
    constexpr ComponentID() = default;
    constexpr ComponentID& operator+=(const int i) noexcept {
        value += i;
        return *this;
    }
};
