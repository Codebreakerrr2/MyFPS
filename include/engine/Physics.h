#pragma once
#include "Entity.h"
#include "PhysicsBody.h"

namespace Physics {


    void InitPhysics();
    void AddRigidBody(int entityID);
    void UpdatePhysics(float deltaTime);
    void syncEntityToBodyPostion(Physics::PhysicsBody* body,Engine::Entity* entity);

}
