#pragma once
#include "asset_manager/Registery.h"
#include "asset_manager/Manager.h"
#include "shader/IShader.h"
#include "mesh/IMesh.h"

namespace Engine {
    class EngineContext {

    public:
        Registery* rg;
        AssetManager::Manager<SHADER::IShader,ShaderID> shaderManger;
        AssetManager::Manager<MESH::IMesh,MeshID> meshManger;


    };
}