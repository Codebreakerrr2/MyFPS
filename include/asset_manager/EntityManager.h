#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "type.h"

namespace Manager {

    /**
     * Manages Entity single point of Responsibility , its not typical Asset Manager. so the Asset Manager Requirement
     * doesn't apply here.
     */


    using EntityID = uint32_t;
    class EntityManager {
        public:
        EntityManager(): nextID(1){};
        ~EntityManager(){DestroyAllEntities();};

        EntityID CreateEntity(const std::string& name);
        void DestroyEntity(EntityID id);
        void DestroyEntity(const std::string& name);
        void DestroyAllEntities();
        Engine::Entity* GetEntity(const std::string& name);
        Engine::Entity* GetEntity(EntityID id);
        
        std::vector<Engine::Entity*> GetAllEntities();


    private:
        EntityID nextID;
       //two data Structures for good performance
        std::vector<std::unique_ptr<Engine::Entity>> entities;
        std::unordered_map<std::string, EntityID> name_map;
        std::unordered_map<EntityID, size_t> id_to_index;
    

    };






}
