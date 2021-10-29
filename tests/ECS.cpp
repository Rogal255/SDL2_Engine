#include "Component.hpp"
#include "ComponentManager.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "HelperTypes.hpp"
#include <cstdio>
#include <gtest/gtest.h>

TEST(ECS, ShouldGenerateEntities) {
    constexpr size_t ENTITIES_TO_GENERATE {100};
    for (size_t i {0}; i < ENTITIES_TO_GENERATE; ++i) {
        ASSERT_EQ(EntityManager::addEntity(), EntityID(i + 1));
    }
    EntityManager::clear();
}

TEST(ECS, ShouldGenerateComponents) {
    ASSERT_THROW(EntityManager::addComponent<TransformComponent>(EntityID(1)), std::invalid_argument);
    constexpr size_t COMPONENTS_TO_GENERATE {100};
    EntityID id;
    for (size_t i {0}; i < COMPONENTS_TO_GENERATE; ++i) {
        id = EntityManager::addEntity();
        EntityManager::addComponent<TransformComponent>(id);
        ASSERT_EQ(EntityManager::getComponentID<TransformComponent>(id), ComponentID(i + 1));
    }
    EntityManager::clear();
    ComponentManager<TransformComponent>::clear();
}

TEST(ECS, ShouldCommunicate) {
    constexpr size_t COMPONENTS_TO_GENERATE {1000};
    EntityID id;
    for (size_t i {0}; i < COMPONENTS_TO_GENERATE; ++i) {
        id = EntityManager::addEntity();
        auto& component = EntityManager::addComponent<TransformComponent>(id);
        component.posX = 1.f * static_cast<float>(i);
        component.posY = 10.f * static_cast<float>(i);
        ASSERT_EQ(EntityManager::getComponent<TransformComponent>(id).posX, 1.f * static_cast<float>(i));
        ASSERT_EQ(EntityManager::getComponent<TransformComponent>(id).posY, 10.f * static_cast<float>(i));
    }
    EntityManager::clear();
    ComponentManager<TransformComponent>::clear();
}

TEST(ECS, ShouldNotDuplicateComponents) {
    constexpr size_t COMPONENTS_TO_GENERATE {100};
    EntityID id;
    for (size_t i {0}; i < COMPONENTS_TO_GENERATE; ++i) {
        id = EntityManager::addEntity();
        auto& component = EntityManager::addComponent<TransformComponent>(id);
        component.posX = 1.f;
        component.posY = 10.f;
        component = EntityManager::addComponent<TransformComponent>(id);
        component = EntityManager::addComponent<TransformComponent>(id);
        component = EntityManager::addComponent<TransformComponent>(id);
        ASSERT_EQ(EntityManager::getComponentID<TransformComponent>(id), ComponentID(i + 1));
        ASSERT_EQ(EntityManager::getComponent<TransformComponent>(id).posX, 1.f);
        ASSERT_EQ(EntityManager::getComponent<TransformComponent>(id).posY, 10.f);
    }
    EntityManager::clear();
    ComponentManager<TransformComponent>::clear();
}

TEST(ECS, ShouldRemoveComponent) {
    ASSERT_THROW(EntityManager::removeComponent<TransformComponent>(EntityID(1)), std::invalid_argument);
    auto firstEntity {EntityManager::addEntity()};
    auto secondEntity {EntityManager::addEntity()};
    auto thirdEntity {EntityManager::addEntity()};
    auto& firstComponent = EntityManager::addComponent<TransformComponent>(firstEntity);
    auto& secondComponent = EntityManager::addComponent<TransformComponent>(secondEntity);
    auto& thirdComponent = EntityManager::addComponent<TransformComponent>(thirdEntity);
    ASSERT_TRUE(EntityManager::hasComponent<TransformComponent>(firstEntity));
    ASSERT_TRUE(EntityManager::hasComponent<TransformComponent>(secondEntity));
    ASSERT_TRUE(EntityManager::hasComponent<TransformComponent>(thirdEntity));
    firstComponent.posX = 1.f;
    secondComponent.posX = 2.f;
    thirdComponent.posX = 3.f;
    ASSERT_EQ(EntityManager::getComponent<TransformComponent>(firstEntity).posX, 1.f);
    ASSERT_EQ(EntityManager::getComponent<TransformComponent>(secondEntity).posX, 2.f);
    ASSERT_EQ(EntityManager::getComponent<TransformComponent>(thirdEntity).posX, 3.f);
    ASSERT_NO_THROW(EntityManager::removeComponent<TransformComponent>(firstEntity));
    ASSERT_THROW(EntityManager::removeComponent<TransformComponent>(firstEntity), std::invalid_argument);
    ASSERT_THROW(EntityManager::removeComponent<TransformComponent>(firstEntity), std::invalid_argument);
    ASSERT_THROW(EntityManager::removeComponent<TransformComponent>(firstEntity), std::invalid_argument);
    ASSERT_FALSE(EntityManager::hasComponent<TransformComponent>(firstEntity));
    ASSERT_TRUE(EntityManager::hasComponent<TransformComponent>(secondEntity));
    ASSERT_TRUE(EntityManager::hasComponent<TransformComponent>(thirdEntity));
    ASSERT_EQ(EntityManager::getComponent<TransformComponent>(secondEntity).posX, 2.f);
    ASSERT_EQ(EntityManager::getComponent<TransformComponent>(thirdEntity).posX, 3.f);
    ASSERT_NO_THROW(EntityManager::removeComponent<TransformComponent>(secondEntity));
    ASSERT_THROW(EntityManager::removeComponent<TransformComponent>(secondEntity), std::invalid_argument);
    ASSERT_THROW(EntityManager::removeComponent<TransformComponent>(secondEntity), std::invalid_argument);
    ASSERT_THROW(EntityManager::removeComponent<TransformComponent>(secondEntity), std::invalid_argument);
    ASSERT_FALSE(EntityManager::hasComponent<TransformComponent>(firstEntity));
    ASSERT_FALSE(EntityManager::hasComponent<TransformComponent>(secondEntity));
    ASSERT_EQ(EntityManager::getComponent<TransformComponent>(thirdEntity).posX, 3.f);
    ASSERT_NO_THROW(EntityManager::removeComponent<TransformComponent>(thirdEntity));
    ASSERT_THROW(EntityManager::removeComponent<TransformComponent>(thirdEntity), std::invalid_argument);
    ASSERT_THROW(EntityManager::removeComponent<TransformComponent>(thirdEntity), std::invalid_argument);
    ASSERT_THROW(EntityManager::removeComponent<TransformComponent>(thirdEntity), std::invalid_argument);
    ASSERT_FALSE(EntityManager::hasComponent<TransformComponent>(firstEntity));
    ASSERT_FALSE(EntityManager::hasComponent<TransformComponent>(secondEntity));
    ASSERT_FALSE(EntityManager::hasComponent<TransformComponent>(thirdEntity));
    ASSERT_THROW(ComponentManager<TransformComponent>::removeComponent(ComponentID(1)), std::invalid_argument);
    EntityManager::clear();
    ComponentManager<TransformComponent>::clear();
}
