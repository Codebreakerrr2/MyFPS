#include <gtest/gtest.h>
#include "asset_manager/Registery.h"
#include "asset_manager/Manager.h"
#include "shader/MockShader.h"
#include "engine/EngineContext.h"
#include "asset_manager/Factory.h"
#include <memory.h>


TEST(RegistryTests, AddAndHasComponent) {
    Engine::Registery rg;

    rg.add<TransformComponent>(1);

    EXPECT_TRUE(rg.has<TransformComponent>(1));
    EXPECT_FALSE(rg.has<TransformComponent>(2));
}
TEST(RegistryTests, RemoveComponent) {
    Engine::Registery rg;

    rg.add<TransformComponent>(1);
    EXPECT_TRUE(rg.has<TransformComponent>(1));

    rg.remove<TransformComponent>(1);

    EXPECT_FALSE(rg.has<TransformComponent>(1));
    EXPECT_EQ(nullptr, rg.get<TransformComponent>(1));
}
TEST(RegistryTests, AddMultipleComponents) {
    Engine::Registery rg;

    auto [t, m] = rg.addComponents<TransformComponent, MeshComponent>(1);

    EXPECT_TRUE(rg.has<TransformComponent>(1));
    EXPECT_TRUE(rg.has<MeshComponent>(1));
}
TEST(RegistryTests, ModifyComponentPersists) {
    Engine::Registery rg;

    auto [t, m] = rg.addComponents<TransformComponent, MeshComponent>(1);

    t.position = Math::Vec3(2.0f);

    EXPECT_TRUE(rg.get<TransformComponent>(1)->position == Math::Vec3(2.0f));
}
TEST(RegisteryTests, RemoveMultipleComponents) {
   Engine::Registery rg;
    rg.addComponents<TransformComponent, MeshComponent>(1);
    rg.remove<TransformComponent, MeshComponent>(1);
    EXPECT_FALSE(rg.has<TransformComponent>(1));
    EXPECT_FALSE(rg.has<MeshComponent>(1));


}
TEST(RegisteryTests, PoolTests) {
    Engine::Registery rg;
    rg.add<TransformComponent>(1);
    const Engine::Registery& rg2 = rg;
    const Asset::Pool<TransformComponent>& transform =rg2.getPool<TransformComponent>();
    EXPECT_TRUE(transform.has(1));

}
TEST(ManagerTests, CreatManager) {
    AssetManager::Manager<SHADER::IShader> shaderManager;
    shaderManager.create("mock",Factory::mockShader);
    Engine::Registery rg;
    rg.add<MaterialComponent>(1,
        MaterialComponent::Init{1,
            [&shaderManager](){return shaderManager.get("mock");},
            Math::Vec3{1}});




}