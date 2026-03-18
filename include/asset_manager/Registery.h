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
        std::vector<Entity> entites;
        std::vector<Entity> renderEntites;
        // hier einfachheitshalber weitere EntitesTypen



        //generic pool to decide which pool is needed. so the type kinda know its pool

    template <typename T>
        auto getPool(T& t) {

    }
        public:
        template<typename T>
        T* get(Entity e) {
            if constexpr (std::is_same_v<T, MeshComponent>) {
                return meshes.getComponent(e.id);
            }
            else if constexpr (std::is_same_v<T, TransformComponent>) {
                return transforms.getComponent(e.id);
            }
            else if constexpr (std::is_same_v<T, MaterialComponent>) {
                return materials.getComponent(e.id);
            }
            // hier eventuell weitere Component hinzufügen wenn die da sind.
        }
        template<typename T>
        void remove(Entity e) {

        }
        template<typename T>
        bool has(Entity e) {
            if constexpr (std::is_same_v<T, MeshComponent>) {
                return meshes.has(e.id);
            }
            else if constexpr (std::is_same_v<T, TransformComponent>) {
                return transforms.has(e.id);
            }
            else if constexpr (std::is_same_v<T, MaterialComponent>) {
                return materials.has(e.id);
            }

        }
        template<typename T>
        T* add(Entity e) {

        }

    };
}