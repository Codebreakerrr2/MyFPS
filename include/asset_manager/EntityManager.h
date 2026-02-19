#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "type.h"

namespace Manager {

    /**
     * Manages Entity single point of Responsibility , its not typical Asset Manager. so the Asset Manager Requirement
     * dosen't apply here.
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
        std::shared_ptr<Engine::Entity> GetEntitySharedP(const std::string& name);
        std::vector<Engine::Entity*> GetAllEntities();


    private:
        EntityID nextID;
       //two data Structures for good performance
        std::vector<std::shared_ptr<Engine::Entity>> entities;
        std::unordered_map<EntityID, std::shared_ptr<Engine::Entity>> entities_map;

    };






}
