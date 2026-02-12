#pragma once
#include "Gizmos.h"
#include "engine/Entity.h"


namespace World {
    class Map;
}
namespace Editor {
    class Editor {




    public:
        Editor(World::Map& map): map(map){};
        void selectObject(Engine::Camera* camera);
        void unselectObject();
        void drawEntities(Engine::Camera& camera);
        void update(float dt, Engine::Camera& camera);
        Engine::Entity* selectedEntity = nullptr;
        World::Map& map;

    private:
        Gizmos gizmos;
        Engine::Camera* selectedCamera = nullptr;

    };
}