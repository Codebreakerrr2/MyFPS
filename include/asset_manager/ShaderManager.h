#pragma once
#include "type.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include "engine/IShader.h"

namespace Engine {
    class OpenGLShader;
}


namespace Manager{

    class ShaderManager {

    private:

        ShaderID nextID= 1;
        std::unordered_map<ShaderID, std::unique_ptr<Engine::IShader>> map;
        std::unordered_map<std::string,ShaderID> name_to_id;
        std::unordered_map<ShaderID,std::string> id_to_name;
        std::vector<ShaderID> shaderRemoveMemory;
      

        bool allDestroyed = false;

        
    public:
  
        Engine::IShader* GetShader(ShaderID id);
        Engine::IShader* GetShader(const std::string& name);
        void DestroyShader(ShaderID id);
        void DestroyShader(const std::string& name);
        Engine::IShader* CreateShader(std::string name,const std::string& pathVertex, const std::string& pathFrag);
        void DestroyAllShaders();
        void cleanUp();

    };
}
