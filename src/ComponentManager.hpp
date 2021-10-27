#pragma once
#include "HelperTypes.hpp"
#include <algorithm>
#include <vector>

template <class T>
class ComponentManager {
public:
    static size_t addComponent(const EntityID& tEntityID) {
        data_.emplace_back(tEntityID);
        return data_.size() - 1;
    }

    // void removeComponent(const size_t index) { data_.erase(data_.begin() + index); }

    static T& getComponent(const size_t& index) { return data_[index]; }

private:
    static inline std::vector<T> data_ {};
};
