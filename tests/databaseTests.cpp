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
    rg.add<MaterialComponent>(1,MaterialComponent::Init{1,&shaderManager});
    rg.get<MaterialComponent>(1)->shader();



}
TEST(ManagerTests, MultipleAssets) {
    AssetManager::Manager<SHADER::IShader> shaderManager;

    // Mehrere Shader erstellen
    shaderManager.create("red_shader", Factory::mockShader);
    shaderManager.create("blue_shader", Factory::mockShader);
    shaderManager.create("green_shader", Factory::mockShader);

    Engine::Registery rg;

    // Entities mit verschiedenen Shadern
    rg.add<MaterialComponent>(1, MaterialComponent::Init{1, &shaderManager});  // red
    rg.add<MaterialComponent>(2, MaterialComponent::Init{2, &shaderManager});  // blue
    rg.add<MaterialComponent>(3, MaterialComponent::Init{3, &shaderManager});  // green

    // Teste dass jeder seinen eigenen Shader hat
    auto* mat1 = rg.get<MaterialComponent>(1);
    auto* mat2 = rg.get<MaterialComponent>(2);
    auto* mat3 = rg.get<MaterialComponent>(3);

    ASSERT_NE(mat1->shader(), mat2->shader());  // Verschiedene Shader
    ASSERT_NE(mat1->shader(), mat3->shader());
    ASSERT_NE(mat2->shader(), mat3->shader());

    // Teste Zugriff über Namen
    EXPECT_EQ(mat1->shader(), shaderManager.get("red_shader"));
    EXPECT_EQ(mat2->shader(), shaderManager.get("blue_shader"));
    EXPECT_EQ(mat3->shader(), shaderManager.get("green_shader"));
}