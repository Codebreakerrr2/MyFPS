#pragma once
#include "asset_manager/types.h"
#include <vector>
#include <unordered_map>


using namespace Engine::Types;
namespace Engine {
    template<class T>
    class Pool{
    public:
        T& emplace(Entity e);
        T& setEntityToComponent(EntityID e, uint32_t componentID); // because ShaderID , EntityID etc.. are/must be uint32_t
        void remove(EntityID e);
        T& getComponent(EntityID e);
        bool has(EntityID e);
        void clear();


    private:
        std::vector<T> components;
        std::vector<EntityID> entities;
        std::unordered_map<EntityID,size_t> lookup;

    };
}