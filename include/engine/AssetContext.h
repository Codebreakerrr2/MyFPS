#pragma once
#include "asset_manager/Manager.h"
#include "asset_manager/Types.h"
#include "shader/IShader.h"
#include "mesh/IMeshPair.h"
namespace Context {
    class AssetContext {
    public:
        AssetManager::Manager<SHADER::IShader, Asset::Types::ShaderID> shaderManger;
        AssetManager::Manager<MESH::IMeshPair, Asset::Types::MeshID> meshManger;

    };
}
