#pragma once
#include "engine/Camera.h"
#include "Math/Vec.h"
#include "geometry/geometry.h"

namespace Geometry {
    struct AABB {
        Math::Vec3 min;
        Math::Vec3 max;
        AABB(Math::Vec3 min, Math::Vec3 max): min(min), max(max) {};
    };

    struct Ray{
        Math::Vec3 origin;
        Math::Vec3 direction;

        Ray(Math::Vec3 origin, Math::Vec3 direction): origin(origin), direction(Math::Normalize(direction)) {}
    };
    Ray GetMouseRay(Engine::Camera* camera);
    bool intersectRayAABB(AABB& aabb, Ray& ray, float &tHit);
    //bool intersectRayRay(Ray ray, Ray ray2); not needed
    bool intersect2AABB(AABB& aabb, AABB& aabb2);
}