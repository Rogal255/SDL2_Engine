#pragma once

template <typename T>
bool GenericComponentManager::checkType() const {
    return T::typeID == typeID_;
}
