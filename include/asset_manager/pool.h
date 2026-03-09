#pragma once
#include "asset_manager/types.h"



template<T>
class Pool{
    public:
    T& emplace(Entity e);
    T& setEntityToComponent(Entity e, uint32_t componentID); // because ShaderID , EntityID etc.. are/must be uint32_t 
    void remove(Entity e);
    T& getComponent(Entity e);
    bool has(Entity e);
    void clear();


    private:
    std::vector<T> components;
    std::vector<EntityID> entities;
    std::unordered_map<EntityID,size_t> lookup;

}


