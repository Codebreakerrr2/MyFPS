#include "asset_manager/ShaderManager.h"
#include <string>
#include "engine/Shader.h"
#include <unordered_map>
#include <memory>
#include <vector>


namespace Manager{

 Engine::Shader* ShaderManager::GetShader(ShaderID id){

    auto it = map.find(id);
    if(it != map.end()){
        return it->second.get();
    }
    return nullptr;
 }

 Engine::Shader* ShaderManager::GetShader(const std::string& name){
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
     Engine::Shader* ShaderManager::CreateShader(std::string name,const std::string& pathVertex, const std::string& pathFrag){
            // erzeuge 
           auto thing =  std::make_unique<Engine::Shader>(pathVertex.c_str(),pathFrag.c_str());


            return nullptr  ;

     }
}

