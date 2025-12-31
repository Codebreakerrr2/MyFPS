#include "engine/Physics.h"

namespace Physics {
    void syncEntityToBodyPostion(Physics::PhysicsBody *body, Engine::Entity *entity) {
            entity->transform.position = body->position;
    }
}
