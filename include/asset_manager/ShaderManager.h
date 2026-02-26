#pragma once
#include "type.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

namespace Engine {
    class Shader;
}


namespace Manager{

    class ShaderManager {

    private:

        ShaderID nextID= 1;
        std::unordered_map<ShaderID, std::unique_ptr<Engine::Shader>> map;
        std::unordered_map<std::string,ShaderID> name_to_id;
        std::unordered_map<ShaderID,std::string> id_to_name;
        std::vector<ShaderID> shaderRemoveMemory;
      

        bool allDestroyed = false;

        
    public:
  
        Engine::Shader* GetShader(ShaderID id);
        Engine::Shader* GetShader(const std::string& name);
        void DestroyShader(ShaderID id);
        void DestroyShader(const std::string& name);
        Engine::Shader* CreateShader(std::string name,const std::string& pathVertex, const std::string& pathFrag);
        void DestroyAllShaders();
        void cleanUp();

    };
}
