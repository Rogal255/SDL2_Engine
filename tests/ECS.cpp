#include "Component.hpp"
#include "ComponentManager.hpp"
#include "GameObservers.hpp"
#include "HelperTypes.hpp"
#include "Scene.hpp"
#include <cstdio>
#include <gtest/gtest.h>

TEST(ECS, ShouldGenerateEntities) {
    GameObservers updateManager;
    Scene scene(&updateManager);
    constexpr size_t ENTITIES_TO_GENERATE {100};
    for (size_t i {0}; i < ENTITIES_TO_GENERATE; ++i) {
        ASSERT_EQ(scene.addEntity(), EntityID(i + 1));
    }
    scene.clear();
}

TEST(ECS, ShouldGenerateComponents) {
    GameObservers updateManager;
    Scene scene(&updateManager);
    ASSERT_THROW(scene.addComponent<TransformComponent>(EntityID(1)), std::invalid_argument);
    constexpr size_t COMPONENTS_TO_GENERATE {100};
    EntityID id;
    for (size_t i {0}; i < COMPONENTS_TO_GENERATE; ++i) {
        id = scene.addEntity();
        scene.addComponent<TransformComponent>(id);
        ASSERT_EQ(scene.getComponentID<TransformComponent>(id), ComponentID(i + 1));
    }
    scene.clear();
}

TEST(ECS, ShouldCommunicate) {
    GameObservers updateManager;
    Scene scene(&updateManager);
    constexpr size_t COMPONENTS_TO_GENERATE {1000};
    EntityID id;
    for (size_t i {0}; i < COMPONENTS_TO_GENERATE; ++i) {
        id = scene.addEntity();
        scene.addComponent<TransformComponent>(id);
        auto& component = scene.getComponent<TransformComponent>(id);
        component.posX = 1.f * static_cast<float>(i);
        component.posY = 10.f * static_cast<float>(i);
        ASSERT_EQ(scene.getComponent<TransformComponent>(id).posX, 1.f * static_cast<float>(i));
        ASSERT_EQ(scene.getComponent<TransformComponent>(id).posY, 10.f * static_cast<float>(i));
    }
    scene.clear();
}

TEST(ECS, ShouldNotDuplicateComponents) {
    GameObservers updateManager;
    Scene scene(&updateManager);
    constexpr size_t COMPONENTS_TO_GENERATE {100};
    EntityID id;
    for (size_t i {0}; i < COMPONENTS_TO_GENERATE; ++i) {
        id = scene.addEntity();
        scene.addComponent<TransformComponent>(id);
        auto& component = scene.getComponent<TransformComponent>(id);
        component.posX = 1.f;
        component.posY = 10.f;
        scene.addComponent<TransformComponent>(id);
        scene.addComponent<TransformComponent>(id);
        scene.addComponent<TransformComponent>(id);
        ASSERT_EQ(scene.getComponentID<TransformComponent>(id), ComponentID(i + 1));
        ASSERT_EQ(scene.getComponent<TransformComponent>(id).posX, 1.f);
        ASSERT_EQ(scene.getComponent<TransformComponent>(id).posY, 10.f);
    }
    scene.clear();
}

TEST(ECS, ShouldRemoveComponent) {
    GameObservers updateManager;
    Scene scene(&updateManager);
    ASSERT_THROW(scene.removeComponent<TransformComponent>(EntityID(1)), std::invalid_argument);
    auto firstEntity {scene.addEntity()};
    auto secondEntity {scene.addEntity()};
    auto thirdEntity {scene.addEntity()};
    scene.addComponent<TransformComponent>(firstEntity);
    scene.addComponent<TransformComponent>(secondEntity);
    scene.addComponent<TransformComponent>(thirdEntity);
    ASSERT_TRUE(scene.hasComponent<TransformComponent>(firstEntity));
    ASSERT_TRUE(scene.hasComponent<TransformComponent>(secondEntity));
    ASSERT_TRUE(scene.hasComponent<TransformComponent>(thirdEntity));
    scene.getComponent<TransformComponent>(firstEntity).posX = 1.f;
    scene.getComponent<TransformComponent>(secondEntity).posX = 2.f;
    scene.getComponent<TransformComponent>(thirdEntity).posX = 3.f;
    ASSERT_EQ(scene.getComponent<TransformComponent>(firstEntity).posX, 1.f);
    ASSERT_EQ(scene.getComponent<TransformComponent>(secondEntity).posX, 2.f);
    ASSERT_EQ(scene.getComponent<TransformComponent>(thirdEntity).posX, 3.f);
    ASSERT_NO_THROW(scene.removeComponent<TransformComponent>(firstEntity));
    ASSERT_THROW(scene.removeComponent<TransformComponent>(firstEntity), std::invalid_argument);
    ASSERT_THROW(scene.removeComponent<TransformComponent>(firstEntity), std::invalid_argument);
    ASSERT_THROW(scene.removeComponent<TransformComponent>(firstEntity), std::invalid_argument);
    ASSERT_FALSE(scene.hasComponent<TransformComponent>(firstEntity));
    ASSERT_TRUE(scene.hasComponent<TransformComponent>(secondEntity));
    ASSERT_TRUE(scene.hasComponent<TransformComponent>(thirdEntity));
    ASSERT_EQ(scene.getComponent<TransformComponent>(secondEntity).posX, 2.f);
    ASSERT_EQ(scene.getComponent<TransformComponent>(thirdEntity).posX, 3.f);
    ASSERT_NO_THROW(scene.removeComponent<TransformComponent>(secondEntity));
    ASSERT_THROW(scene.removeComponent<TransformComponent>(secondEntity), std::invalid_argument);
    ASSERT_THROW(scene.removeComponent<TransformComponent>(secondEntity), std::invalid_argument);
    ASSERT_THROW(scene.removeComponent<TransformComponent>(secondEntity), std::invalid_argument);
    ASSERT_FALSE(scene.hasComponent<TransformComponent>(firstEntity));
    ASSERT_FALSE(scene.hasComponent<TransformComponent>(secondEntity));
    ASSERT_EQ(scene.getComponent<TransformComponent>(thirdEntity).posX, 3.f);
    ASSERT_NO_THROW(scene.removeComponent<TransformComponent>(thirdEntity));
    ASSERT_THROW(scene.removeComponent<TransformComponent>(thirdEntity), std::invalid_argument);
    ASSERT_THROW(scene.removeComponent<TransformComponent>(thirdEntity), std::invalid_argument);
    ASSERT_THROW(scene.removeComponent<TransformComponent>(thirdEntity), std::invalid_argument);
    ASSERT_FALSE(scene.hasComponent<TransformComponent>(firstEntity));
    ASSERT_FALSE(scene.hasComponent<TransformComponent>(secondEntity));
    ASSERT_FALSE(scene.hasComponent<TransformComponent>(thirdEntity));
    scene.clear();
}
