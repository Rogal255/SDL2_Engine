#include "Scene.hpp"

EntityID Scene::addEntity() noexcept { return entityManager.addEntity(); }

void Scene::removeEntity(const EntityID& tEntityID) {
    if (hasComponent<TransformComponent>(tEntityID)) {
        removeComponent<TransformComponent>(tEntityID);
    }
    entityManager.removeEntity(tEntityID);
}

void Scene::clear() {
    entityManager.clear();
    getComponentManager<TransformComponent>().clear();
    getComponentManager<SpriteComponent>().clear();
}
