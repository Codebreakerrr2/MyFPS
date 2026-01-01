#pragma once
#include "math/Vec.h"


namespace Physics {
    struct PhysicsBody {

        float mass=1.0f;
        float friction=2.0f;
        float gravity=0;
        Math::Vec3 position;
        Math::Vec3 velocity ;
        float accelerationRate = 10.0f;
    };
}
