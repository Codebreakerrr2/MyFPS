#include <asset_manager/ShaderManager.h>
#include <gtest/gtest.h>
#include "asset_manager/ShaderManager.h"
#include <string>
#include "engine/Shader.h"
#include <unordered_map>
#include <memory>
#include <vector>




TEST(AssetManager, ShaderManager) {

// creat Shaders check if inside the map, persistent and synchronicity of maps after each funktion called.

Manager::ShaderManager shaderManager;
    shaderManager.CreateShader("name","assets/shaders/basic.vert","assets/shaders/bild.frag");





}