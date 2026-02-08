#pragma once
#include "Gizmos.h"
#include "engine/Entity.h"


class Editor {

    public:
    void selectObject();
    void unselectObject();
    void update(float dt);
    Engine::Entity* selectedEntity = nullptr;

private:
    Gizmos gizmos;

};
