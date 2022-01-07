#include "Scene.hpp"

EntityID Scene::addEntity() noexcept { return manager_.addEntity(); }

void Scene::removeEntity(const EntityID& tEntityID) { manager_.removeEntity(tEntityID); }

void Scene::clear() { manager_.clear(); }
