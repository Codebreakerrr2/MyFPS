#include "asset_manager/ShaderManager.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include "engine/Renderer.h"


namespace Manager{

 Engine::IShader* ShaderManager::GetShader(ShaderID id){

    auto it = map.find(id);
    if(it != map.end()){
        return it->second.get();
    }
    return nullptr;
 }

 Engine::IShader* ShaderManager::GetShader(const std::string& name){
    auto it = name_to_id.find(name);
    if(it != name_to_id.end()){
        ShaderID id = it->second; 
        return GetShader(id);
    }
    return nullptr;
    }

    void ShaderManager::DestroyShader(ShaderID id){

         shaderRemoveMemory.push_back(id);

    }
    void ShaderManager::DestroyShader(const std::string& name){
       
        auto it = name_to_id.find(name);
        if(it != name_to_id.end()){
            shaderRemoveMemory.push_back(it->second);
        }

    }   
    void ShaderManager::DestroyAllShaders(){
            allDestroyed = true;
    }
    void ShaderManager::cleanUp(){
        if(allDestroyed){
            name_to_id.clear();
            id_to_name.clear();
            map.clear();
            shaderRemoveMemory.clear();
        }
        for(auto& rm : shaderRemoveMemory){
            map.erase(rm);
           auto iter = id_to_name.find(rm);
           if(iter!=id_to_name.end()){
            name_to_id.erase(iter->second);
            id_to_name.erase(iter);
           }
        }
        shaderRemoveMemory.clear();


    }
     Engine::IShader* ShaderManager::CreateShader(std::string name,const std::string& pathVertex, const std::string& pathFrag){
            // erzeuge
            Engine::IShader* ptr;
     switch(Engine::GetRenderType()) {





     }


            return nullptr  ;
     }

     //--------------------------------TEST_____FUNCTION--------------------------------------

      Engine::OpenGLShader* ShaderManager::CreateShaderMock(std::string name,const std::string& pathVertex, const std::string& pathFrag){
            // erzeuge 
           auto thing =  std::make_unique<Engine::IShader>(CreateShader(pathVertex.c_str(),pathFrag.c_str());
            
    ShaderID id = nextID++;
    name_to_id[name] = id;
    id_to_name[id] = name;
    Engine::OpenGLShader* ptr = thing.get();
    map[id] = std::move(thing);
    return ptr;


     }
}

