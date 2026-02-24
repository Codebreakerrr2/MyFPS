#include "asset_manager/EntityManager.h"
#include "engine/Entity.h"
#include <algorithm>


namespace Manager {
    EntityID EntityManager::CreateEntity(const std::string &name) {

        //if Entity already Exists give ID.
        if (auto existing = GetEntity(name)) {
            return existing->id;
        }
        auto ent = std::make_unique<Engine::Entity>();
        ent->name = name;
        ent->id = nextID++;
        Engine::Entity* rawPtr = ent.get();
        entities.push_back(std::move(ent));
        size_t index = entities.size()-1;
        id_to_index[rawPtr->id] = index;
        name_to_id[name] = rawPtr->id;
        return rawPtr->id;
    }

  void EntityManager::DestroyEntity(EntityID id)
{
    auto it = id_to_index.find(id);
    if (it == id_to_index.end())
        return;

    size_t index = it->second;
    size_t lastIndex = entities.size() - 1;
     name_to_id.erase(entities[index]->name);
    if (index != lastIndex)
    {
        std::swap(entities[index], entities[lastIndex]);

        // Update index of swapped entity
        id_to_index[entities[index]->id] = index;
    }

    entities.pop_back();        // IMMER poppen
    id_to_index.erase(id);      // IMMER ID löschen

}




    void EntityManager::DestroyEntity(const std::string &name) {
      // find the Entity if not do nothing
      auto it = name_to_id.find(name);
      if(it != name_to_id.end()){
            size_t id = it->second;
            DestroyEntity(id);

      }
    }

    void EntityManager::DestroyAllEntities() {
            entities.clear();
            name_to_id.clear();
            id_to_index.clear();
    }

    Engine::Entity * EntityManager::GetEntity(const std::string &name) {
            auto it = name_to_id.find(name);
            if(it!= name_to_id.end()){
                EntityID id = it->second;
              return  GetEntity(id);
    }
    return nullptr;
    }
    Engine::Entity * EntityManager::GetEntity(EntityID id) {
               auto it = id_to_index.find(id);
                if(it!= id_to_index.end()){
                    return entities[it->second].get();
                }
                return nullptr;
            }
    
    

    std::vector<Engine::Entity *> EntityManager::GetAllEntities() {
         std::vector<Engine::Entity*> result;
         result.reserve(entities.size());
         for(auto& it : entities){
            result.push_back(it.get());
         }
         return result;

        }
}
