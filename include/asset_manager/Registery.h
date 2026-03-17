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
        Pool<MeshComponent> meshes;
        Pool<TransformComponent> transforms;
        Pool<MaterialComponent> materials;
        std::vector<Entity> entites;
        std::vector<Entity> renderEntites;
        // hier einfachheitshalber weitere EntitesTypen
        
        public:
        template<typename T>
        T* get(Entity e){

            if constexpr(std::is_same_v(T,transforms){
                return transforms.get(e);
            }
            if else constexpr (std::ist_same_v(T,materials)){
                return materials.shader();
            }



        }



    };
}