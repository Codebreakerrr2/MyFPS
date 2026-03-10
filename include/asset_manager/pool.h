#pragma once
#include "asset_manager/types.h"
#include <vector>
#include <unordered_map>
#include "profiling/LoggerManager.h"


constexpr size_t INVALID_INDEX = size_t(-1);

using namespace Engine::Types;
namespace Engine {
    template<class T>
    class Pool{
    public:
     
        T& emplace(EntityID e){
            size_t eIndex = entities.size();
            entities.push_back(e);
    
            size_t sparseLenght = sparse.size();
            if(e > sparseLenght-1){
                sparse.resize(e+10 ,INVALID_INDEX);
            }
            sparse[e] = eIndex;

            components.emplace_back(T{});

            LOG_SUCCESS("Component and Entity added to the Pool");

            return components.back();
        }


        void remove(EntityID e){

            if(entities.size() < 1 || !has(e)) {

                LOG_DEBUG("entity not found the pool");   

                return;
            }
            if(entities.size()> 1){
               


            // swap e mit letzem element
            swapEntities(e,entities.back());
            sparse[e] = INVALID_INDEX;
            entities.pop_back();
            components.pop_back();

            LOG_SUCCESS("entity succesfully removed from pool");

            }
        }
        T* getComponent(EntityID e){
            if(!has(e)){ 

                LOG_DEBUG("entity not found the pool"); 

                return nullptr;
            }
            return &components[sparse[e]];

        }
        bool has(EntityID e){
            return e<sparse.size() && sparse[e] != INVALID_INDEX;
        }
        void clear(){
            entities.clear();
            components.clear();
            sparse.clear();

            entities.shrink_to_fit();
            components.shrink_to_fit();
            sparse.shrink_to_fit();

            LOG_SUCCESS("Pool has been cleared!");
        }


    private:
        void swapEntities(EntityID e1, EntityID e2){
            //if last Element
            if(e1 != e2){
           
              size_t e1Index =  sparse[e1];
              size_t e2Index = sparse[e2];

              std::swap(entities[e1Index],entities[e2Index]);
              std::swap(components[e1Index],components[e2Index]);
              sparse[e2] = e1Index; 
              sparse[e1] = e2Index;
            }

        }
        
        std::vector<T> components;
        std::vector<EntityID> entities;
        std::vector<size_t> sparse;

    };
}