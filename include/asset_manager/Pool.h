#pragma once
#include "asset_manager/Types.h"
#include <vector>
#include "profiling/LoggerManager.h"
#include <utility>

constexpr size_t INVALID_INDEX = size_t(-1);

using namespace Asset::Types;
namespace Asset {
    template<class T>
    class Pool{
    public:
     template<typename... Args>
        T& emplace(EntityID e, Args&&... args){
            if (has(e)) {

                LOG_WARNING("Entity already exits, can't add!");
                
                return components[sparse[e]];
            }
            size_t eIndex = entities.size();
            entities.push_back(e);
    
            size_t sparseLenght = sparse.size();
            if(e >= sparseLenght){
                sparse.resize(e+10 ,INVALID_INDEX);
            }
            sparse[e] = eIndex;

            components.emplace_back(std::forward<Args>(args)...);

            LOG_SUCCESS("Component and Entity added to the Pool");

            return components.back();
        }


        void remove(EntityID e){

            if(!has(e)) {

                LOG_DEBUG("entity not found im the pool");

                return;
            }

               


            // swap e mit letzem element
            swapEntities(e,entities.back());
            sparse[e] = INVALID_INDEX;
            entities.pop_back();
            components.pop_back();

            LOG_SUCCESS("entity succesfully removed from pool");


        }
        T* getComponent(EntityID e){
            if(!has(e)){

                LOG_DEBUG("entity not found in the pool");

                return nullptr;
            }
            return &components[sparse[e]];

        }
        const T* getComponent(EntityID e) const {
         if(!has(e)){

             LOG_DEBUG("entity not found in the pool");

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


            LOG_SUCCESS("Pool has been cleared!");
        }


    private:
        void swapEntities(EntityID e1, EntityID e2){
            assert(has(e1) && has(e2));

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