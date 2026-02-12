#include "editor/Editor.h"
#include "World/Map.h"
#include <cfloat>

#include "engine/Input.h"
#include "engine/Renderer.h"

namespace Editor {
    void Editor::drawEntities(Engine::Camera& camera) {
        for (Engine::Entity* entity: map.entities) {
            Engine::RenderEntity(*entity,camera);
        }
    }


    void Editor::selectObject(Engine::Camera* camera)  {
        //shot ray if ray intersect with the nearest object then select that object
        Geometry::Ray ray = Geometry::GetMouseRay(camera);
        //check for all objects in map if ray intersect chose the nearest object as selected
        Engine::Entity* result =nullptr;
        float Tnear = FLT_MAX;

        for (Engine::Entity* entity : map.entities) {
            Geometry::AABB box = entity->GetAABB();
            float TLoop;
            if (Geometry::intersectRayAABB( box ,ray, TLoop)){
                if (Tnear > TLoop) {
                    Tnear = TLoop;
                    result = entity;
                }
            }
        }
        selectedEntity=result;
    }

    void Editor::unselectObject() {
        selectedEntity = nullptr;
    }

    void Editor::update(float dt,Engine::Camera& camera ) {
        if (Engine::IsKeyPressed(GLFW_KEY_Q)) {
            selectObject(&camera);
        }
        if (selectedEntity){
            gizmos.drawGizmos(*selectedEntity,camera);
            gizmos.manipulateEntity(*selectedEntity);
        }
    }
}
