#include <asset_manager/ShaderManager.h>
#include <gtest/gtest.h>
#include "asset_manager/ShaderManager.h"
#include <string>
#include "engine/Shader.h"
#include <unordered_map>
#include <memory>
#include <vector>

TEST(AssetManager, ShaderManager_CreateAndGet) {
    Manager::ShaderManager shaderManager;

    // 3 Mock-Shader erstellen
    auto* s1 = shaderManager.CreateShaderMock("name1", "v1", "f1");
    auto* s2 = shaderManager.CreateShaderMock("name2", "v2", "f2");
    auto* s3 = shaderManager.CreateShaderMock("name3", "v3", "f3");

    // Shader existieren
    EXPECT_NE(s1, nullptr);
    EXPECT_NE(s2, nullptr);
    EXPECT_NE(s3, nullptr);

    // GetShader by Name
    EXPECT_EQ(shaderManager.GetShader("name1"), s1);
    EXPECT_EQ(shaderManager.GetShader("name2"), s2);
    EXPECT_EQ(shaderManager.GetShader("name3"), s3);

    // GetShader by ID
    EXPECT_EQ(shaderManager.GetShader(s1->ID), s1);
    EXPECT_EQ(shaderManager.GetShader(s2->ID), s2);
    EXPECT_EQ(shaderManager.GetShader(s3->ID), s3);
}

TEST(AssetManager, ShaderManager_DestroyIndividual) {
    Manager::ShaderManager shaderManager;

    auto* s1 = shaderManager.CreateShaderMock("name1", "v1", "f1");
    auto* s2 = shaderManager.CreateShaderMock("name2", "v2", "f2");

    // Shader s1 zerstören
    shaderManager.DestroyShader(s1->ID);
    shaderManager.cleanUp();

    EXPECT_EQ(shaderManager.GetShader("name1"), nullptr);
    EXPECT_EQ(shaderManager.GetShader(s1->ID), nullptr);

    // s2 sollte noch existieren
    EXPECT_EQ(shaderManager.GetShader("name2"), s2);
    EXPECT_EQ(shaderManager.GetShader(s2->ID), s2);

    // Shader s2 über Name zerstören
    shaderManager.DestroyShader("name2");
    shaderManager.cleanUp();

    EXPECT_EQ(shaderManager.GetShader("name2"), nullptr);
    EXPECT_EQ(shaderManager.GetShader(s2->ID), nullptr);
}

TEST(AssetManager, ShaderManager_DestroyAll) {
    Manager::ShaderManager shaderManager;

    shaderManager.CreateShaderMock("name1", "v1", "f1");
    shaderManager.CreateShaderMock("name2", "v2", "f2");
    shaderManager.CreateShaderMock("name3", "v3", "f3");

    // Alle Shader zerstören
    shaderManager.DestroyAllShaders();
    shaderManager.cleanUp();

    EXPECT_EQ(shaderManager.GetShader("name1"), nullptr);
    EXPECT_EQ(shaderManager.GetShader("name2"), nullptr);
    EXPECT_EQ(shaderManager.GetShader("name3"), nullptr);
}

TEST(AssetManager, ShaderManager_UniqueIDs) {
    Manager::ShaderManager shaderManager;

    auto* s1 = shaderManager.CreateShaderMock("name1", "v1", "f1");
    auto* s2 = shaderManager.CreateShaderMock("name2", "v2", "f2");
    auto* s3 = shaderManager.CreateShaderMock("name3", "v3", "f3");

    // Prüfen, dass alle IDs unterschiedlich sind
    EXPECT_NE(s1->ID, s2->ID);
    EXPECT_NE(s1->ID, s3->ID);
    EXPECT_NE(s2->ID, s3->ID);
}
