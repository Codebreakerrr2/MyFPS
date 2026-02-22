#pragma once
#include "type.h"
#include <unordered_map>
#include <memory>
#include <vector>

namespace Engine {
    class Shader;
}


namespace Manager{

class ShaderManager {

private:

    ShaderID nextID;
    std::unordered_map<ShaderID, std::unique_ptr<Engine::Shader>> map; 
    std::unordered_map<std::string,ShaderID> nameToIdMap;
    std::vector<ShaderID> shaderRemoveMemory;
public:
    Engine::Shader* GetShader(ShaderID id);
    Engine::Shader* GetShader(const std::string& name);
    void DestroyShader(ShaderID id);
    void DestroyShader(const std::string& name);
    Engine::Shader* CreatShader(std::string name,const std::string& pathVertex, const std::string& pathFrag);


        };
}
