#pragma once
#include <cassert>

#include "asset_manager/Types.h"
#include <vector>
#include "profiling/LoggerManager.h"
#include <utility>

#include "physics/AABB/AABBSystem.h"

constexpr size_t INVALID_INDEX = size_t(-1);

using namespace Asset::Types;
namespace Asset {


    template <typename T>
std::string getPoolName() {
        if constexpr (std::is_same_v<T, MeshComponent>) {
            return "meshesPool";
        } else if constexpr (std::is_same_v<T, TransformComponent>) {
            return "transformsPool";
        } else if constexpr (std::is_same_v<T, MaterialComponent>) {
            return "materialsPool";
        }
        else if constexpr (std::is_same_v<T,Physics::AABBSystem::AABBComponent>){
            return "AABBsPool";
        } else {
            static_assert(!std::is_same_v<T, T>, "Unsupported component type to get name");
            return ""; // nur um den Compiler zufriedenzustellen
        }
    }


    template<class T>
    class Pool{
    public:
     template<typename... Args>
        T& emplace(EntityID e, Args&&... args){
            if (has(e)) {

                LOG_WARNING("Entity "+ std::to_string(e)+ " already exits, can't add!, instead returning Entity");
                
                return components[sparse[e]];
            }
            size_t eIndex = entities.size();
            entities.push_back(e);
    
            size_t sparseLenght = sparse.size();
            if(e >= sparseLenght){
                sparse.resize(e*2 ,INVALID_INDEX);
            }
            sparse[e] = eIndex;

            components.emplace_back(std::forward<Args>(args)...);

            LOG_SUCCESS("Component "+getComponentName<T>()+ " with Entity "+std::to_string(e)+" added to the Pool");

            return components.back();
        }


        void remove(EntityID e){

            if(!has(e)) {

                LOG_DEBUG("entity "+ std::to_string(e) +" not found im the pool");

                return;
            }

               


            // swap e mit letzem element
            swapEntities(e,entities.back());
            sparse[e] = INVALID_INDEX;
            entities.pop_back();
            components.pop_back();

            LOG_SUCCESS("entity "+std::to_string(e) +" succesfully removed from pool");


        }
        T* getComponent(EntityID e){
            if(!has(e)){

                LOG_DEBUG("entity "+ std::to_string(e) +" not found im the pool");
                return nullptr;
            }
            return &components[sparse[e]];

        }
        const T* getComponent(EntityID e) const {
         if(!has(e)){

             LOG_DEBUG("entity "+ std::to_string(e) +" not found im the pool");

             return nullptr;
         }
         return &components[sparse[e]];

     }
        bool has(EntityID e) const {
            return e<sparse.size() && sparse[e] != INVALID_INDEX;
        }
        void clear(){
            entities.clear();
            components.clear();
            sparse.clear();


            LOG_SUCCESS("Pool "+ getPoolName<T>()+ " has been cleared!");
        }
        const std::vector<EntityID>& getEntities() const{
            return entities;
        }


    private:
        void swapEntities(EntityID e1, EntityID e2){
            //..........................................
            assert(has(e1) && has(e2));// gefährlich
            //..........................................(
            if(e1 == e2) return;

            size_t e1Index = sparse[e1];
            size_t e2Index = sparse[e2];

            std::swap(entities[e1Index], entities[e2Index]);
            std::swap(components[e1Index], components[e2Index]);

            sparse[e1] = e2Index;
            sparse[e2] = e1Index;

        }
        
        std::vector<T> components;
        std::vector<EntityID> entities;
        std::vector<size_t> sparse;

    };


}