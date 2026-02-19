#include "asset_manager/EntityManager.h"
#include "engine/Entity.h"
#include <algorithm>


namespace Manager {
    EntityID EntityManager::CreateEntity(const std::string &name) {

        //if Entity already Exists give ID.
        if (auto existing = GetEntity(name)) {
            return existing->id;
        }
        auto ent = std::make_shared<Engine::Entity>();
        ent->name = name;
        ent->id = nextID++;
        entities.push_back(ent);
        entities_map[ent->id] = ent;
        return ent->id;
    }

    void EntityManager::DestroyEntity(EntityID id) {
        //find entity if not do nothing
        auto it = entities_map.find(id);
        if (it != entities_map.end()) {
            entities.erase(std::remove(entities.begin(),entities.end(),it->second),entities.end());
            entities_map.erase(it);
            }
    }




    void EntityManager::DestroyEntity(const std::string &name) {
        std::shared_ptr<Engine::Entity> entitySharedPtr = GetEntitySharedP(name);
        if (entitySharedPtr) {
            entities_map.erase(entitySharedPtr->id);

            auto it = std::find(entities.begin(),entities.end(),entitySharedPtr);
            if (it != entities.end()) {

            }

        }
    }

    void EntityManager::DestroyAllEntities() {
    }

    Engine::Entity * EntityManager::GetEntity(const std::string &name) {
    }

    Engine::Entity * EntityManager::GetEntity(EntityID id) {
    }
    std::shared_ptr<Engine::Entity> GetEntitySharedP(const std::string& name) {

    }

    std::vector<Engine::Entity *> EntityManager::GetAllEntities() {
    }
}
