#include "asset_manager/pool.h"



namespace Engine {
    template<class T>
    T& Pool<T>::emplace(Entity e) {
        entities.push_back(e);
        components.push_back(e);

    }
}
