#include "editor/Editor.h"
#include "World/Map.h"
#include <cfloat>


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

void Editor::update(float dt) {
    if (selectedEntity){
        gizmos.drawGizmos(*selectedEntity);
        gizmos.manipulateEntity(*selectedEntity);
    }
}
