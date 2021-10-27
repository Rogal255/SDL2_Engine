#include "Component.hpp"
#include "ComponentManager.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "HelperTypes.hpp"
#include <cstdio>
#include <gtest/gtest.h>

TEST(ECS, ShouldGenerateEntities) {
    EntityManager manager;
    constexpr size_t ENTITIES_TO_GENERATE {100};
    for (size_t i {0}; i < ENTITIES_TO_GENERATE; ++i) {
        ASSERT_EQ(manager.addEntity(), EntityID(i + 1));
    }
}

TEST(ECS, ShouldGenerateComponents) {
    EntityManager manager;
    constexpr size_t COMPONENTS_TO_GENERATE {100};
    EntityID id;
    for (size_t i {0}; i < COMPONENTS_TO_GENERATE; ++i) {
        id = manager.addEntity();
        manager.addComponent<TransformComponent>(id);
        ASSERT_EQ(manager.getComponentID<TransformComponent>(id), ComponentID(i + 1));
    }
}

TEST(ECS, ShouldCommunicate) {
    EntityManager manager;
    constexpr size_t COMPONENTS_TO_GENERATE {1000};
    EntityID id;
    for (size_t i {0}; i < COMPONENTS_TO_GENERATE; ++i) {
        id = manager.addEntity();
        auto& component = manager.addComponent<TransformComponent>(id);
        component.posX = 1.f * static_cast<float>(i);
        component.posY = 10.f * static_cast<float>(i);
        ASSERT_EQ(manager.getComponent<TransformComponent>(id).posX, 1.f * static_cast<float>(i));
        ASSERT_EQ(manager.getComponent<TransformComponent>(id).posY, 10.f * static_cast<float>(i));
    }
}
