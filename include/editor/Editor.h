#pragma once
#include "Gizmos.h"
#include "engine/Entity.h"


namespace World {
    class Map;
}
namespace Editor {
    class Editor {


        Math::Vec3 selectedEntityColor = Math::Vec3(1.0f, 1.0f, 0.6f);

    public:
        Editor(World::Map& map): map(map) ,EditorShader("assets/shaders/basic.vert", "assets/shaders/editor_overlay.frag"){};
        void selectObject(Engine::Camera* camera);
        void unselectObject();
        void drawEntities(Engine::Camera& camera);
        void update(float dt, Engine::Camera& camera);
        Engine::Entity* selectedEntity = nullptr;
        World::Map& map;
        Engine::Shader EditorShader;

    private:
        Gizmos gizmos;
        Engine::Camera* selectedCamera = nullptr;

    };
}