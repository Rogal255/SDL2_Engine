#pragma once
#include <algorithm>
#include <vector>

template <class T>
class ComponentManager {
public:
    static size_t addComponent() {
        data_.emplace_back();
        return data_.size() - 1;
    }

    // void removeComponent(const size_t index) { data_.erase(data_.begin() + index); }

    static T& getComponent(const size_t index) { return data_[index]; }

private:
    static inline std::vector<T> data_ {};
};
