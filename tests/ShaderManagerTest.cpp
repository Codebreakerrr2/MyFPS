#include <asset_manager/ShaderManager.h>
#include <gtest/gtest.h>
#include "asset_manager/ShaderManager.h"
#include <string>
#include "engine/Shader.h"
#include <unordered_map>
#include <memory>
#include <vector>

using namespace Manager;

TEST(ShaderManager, CreateAndGetShaders) {
    ShaderManager shaderManager;

    // Setze RenderType auf DummyShader für den Test
    Engine::SetRenderType(RenderType::DummyShader);

    // Shader erstellen
    Engine::IShader* s1 = shaderManager.CreateShader("name1", "v1", "f1");
    Engine::IShader* s2 = shaderManager.CreateShader("name2", "v2", "f2");
    Engine::IShader* s3 = shaderManager.CreateShader("name3", "v3", "f3");

    // Alle Shader sollen in den Maps sein
    EXPECT_EQ(shaderManager.GetShader("name1"), s1);
    EXPECT_EQ(shaderManager.GetShader("name2"), s2);
    EXPECT_EQ(shaderManager.GetShader("name3"), s3);

    EXPECT_EQ(shaderManager.GetShader(1), s1);
    EXPECT_EQ(shaderManager.GetShader(2), s2);
    EXPECT_EQ(shaderManager.GetShader(3), s3);
}

TEST(ShaderManager, DestroyIndividualShader) {
    ShaderManager shaderManager;
    Engine::SetRenderType(RenderType::DummyShader);

    Engine::IShader* s1 = shaderManager.CreateShader("name1", "v1", "f1");
    Engine::IShader* s2 = shaderManager.CreateShader("name2", "v2", "f2");

    // s1 löschen
    shaderManager.DestroyShader(1);
    shaderManager.cleanUp();

    EXPECT_EQ(shaderManager.GetShader("name1"), nullptr);
    EXPECT_EQ(shaderManager.GetShader(1), nullptr);

    // s2 existiert noch
    EXPECT_EQ(shaderManager.GetShader("name2"), s2);
    EXPECT_EQ(shaderManager.GetShader(2), s2);

    // s2 löschen über Name
    shaderManager.DestroyShader("name2");
    shaderManager.cleanUp();

    EXPECT_EQ(shaderManager.GetShader("name2"), nullptr);
    EXPECT_EQ(shaderManager.GetShader(2), nullptr);
}

TEST(ShaderManager, DestroyAllShaders) {
    ShaderManager shaderManager;
    Engine::SetRenderType(RenderType::DummyShader);

    shaderManager.CreateShader("name1", "v1", "f1");
    shaderManager.CreateShader("name2", "v2", "f2");
    shaderManager.CreateShader("name3", "v3", "f3");

    shaderManager.DestroyAllShaders();
    shaderManager.cleanUp();

    EXPECT_EQ(shaderManager.GetShader("name1"), nullptr);
    EXPECT_EQ(shaderManager.GetShader("name2"), nullptr);
    EXPECT_EQ(shaderManager.GetShader("name3"), nullptr);
}

TEST(ShaderManager, UniqueIDs) {
    ShaderManager shaderManager;
    Engine::SetRenderType(RenderType::DummyShader);

    Engine::IShader* s1 = shaderManager.CreateShader("name1", "v1", "f1");
    Engine::IShader* s2 = shaderManager.CreateShader("name2", "v2", "f2");
    Engine::IShader* s3 = shaderManager.CreateShader("name3", "v3", "f3");

    // IDs müssen einzigartig sein
    EXPECT_NE(s1->ID, s2->ID);
    EXPECT_NE(s1->ID, s3->ID);
    EXPECT_NE(s2->ID, s3->ID);
}