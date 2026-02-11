//
// Created by usman on 18.12.2025.
//

#include "world/Map.h"
#include "engine/Camera.h"
#include <algorithm>

#include "engine/Renderer.h"

void World::Map::addEntity(Engine::Entity *entity) {
    if (entity && std::find(entities.begin(),entities.end(),entity)==entities.end()) {
        entities.push_back(entity);
    }
}

void World::Map::removeEntity(Engine::Entity *entity) {
    auto it = std::find(entities.begin(),entities.end(),entity);
    if (it != entities.end()) {
        entities.erase(it);
    }
}

void World::Map::RenderMap(Engine::Camera& camera) {
    for (auto it : entities) {
        if (!it) continue;
        Engine::RenderEntity(*it, camera);
    }
}
