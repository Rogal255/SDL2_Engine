#pragma once
#include <cstdint>

class Updatable {
public:
    virtual void update(uint32_t) = 0;
    virtual ~Updatable() = default;
};
