#pragma once
#include "Gizmos.h"
#include "engine/Entity.h"


namespace World {
    class Map;
}

class Editor {


    Editor(World::Map& map): map(map){};

    public:
    void selectObject(Engine::Camera* camera);
    void unselectObject();
    void update(float dt);
    Engine::Entity* selectedEntity = nullptr;
    World::Map& map;

private:
    Gizmos gizmos;

};
