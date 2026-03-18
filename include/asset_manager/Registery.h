#pragma once
#include "asset_manager/pool.h"
#include "asset_manager/Types.h"
#include "asset_manager/Registery.h"
#include <vector>
/**
 * Registery is the API for other Systems to get access to assets
 */
namespace Engine {
    class Registery {

        private:
        Asset::Pool<MeshComponent> meshes;
        Asset::Pool<TransformComponent> transforms;
        Asset::Pool<MaterialComponent> materials;
        std::vector<ComponentMask> masks;




//generic pool to decide which pool is needed. so the type kinda know its pool, its private 
//___________________________________________________________________________________________________________________//
    template <typename T>
    Asset::Pool<T>& getPool(){
        if constexpr (std::is_same_v<T, MeshComponent>){
            return meshes;
        }
        else if constexpr (std::is_same_v<T, TransformComponent>){
            return transforms;
        }
        else if constexpr (std::is_same_v<T, MaterialComponent>){
            return materials;
        }
        else{static_assert(!std::is_same_v<T, T>, "Unsupported component type in Registry::getPool");}
    // more pools can be added must be added here


    }
       
//________________________________________________________________________________________________________________________________//



        public:

//_________________Pool public only Read for performance and less boilerplate_____________________//
         template <typename T>
     const Asset::Pool<T>& getPool() const {
        if constexpr (std::is_same_v<T, MeshComponent>){
            return meshes;
        }
        else if constexpr (std::is_same_v<T, TransformComponent>){
            return transforms;
        }
        else if constexpr (std::is_same_v<T, MaterialComponent>){
            return materials;
        }
        else{static_assert(!std::is_same_v<T, T>, "Unsupported component type in Registry::getPool");}
    // more pools can be added must be added here


    }
 //__________________________________________________________________________________________________//



        template<typename T>
        T* get(EntityID e) {
           return  getPool<T>().getComponent(e);
        }
        template<typename T>
        const T* get(EntityID e) const {
           return  getPool<T>().getComponent(e);
        }



        template<typename T>
        void remove(EntityID e) {
            getPool<T>().remove(e);  
            masks[e] =(~ComponentToType<T>()) & masks[e];

        }

        template<typename... Components>
        void remove(EntityID e){
            (getPool<Components>().remove(e),...);
            (masks[e] =(~ComponentToType<Components>()) & masks[e],...);
        }


        template<typename T>
        bool has(EntityID e) {
            return masks[e] & ComponentToType<T>() != 0;
        }


        template<typename T>
        T& add(EntityID e) {
            if(e >= masks.size()){
                masks.resize(e+10,0);
            }
            masks[e] |= ComponentToType<T>();
            return getPool<T>().emplace(e);

        }


        template<typename... Components>
        auto addComponents(EntityID e){
               if(e >= masks.size()){
                masks.resize(e+10,0);
            }
            (masks[e] |= ComponentToType<Components>(),...);

            return std::make_tuple(getPool<Components>().emplace(e)...);
        }
       
    };
}