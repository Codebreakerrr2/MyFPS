#pragma once
#include "AABB_ADT.h"
#include "renderer/IRenderer.h"

namespace Physics::AABBSystem {

    struct AABBComponent {
        AABB_ADT::AABB worldAABB;
        bool dirty  = true;
    };
    struct AABBQueryItem {
        Asset::Types::Entity entity;
        AABB_ADT::AABB worldAABB;
    };

    struct CollisionEvent {
        Asset::Types::Entity entity1;
        Asset::Types::Entity entity2;
    };

    struct RaycastHit {
        Asset::Types::Entity entity;
        Math::Vec3 intersection;
        AABB_ADT::Ray ray;
    };

   std::vector<CollisionEvent> getCollisions(const std::vector<AABBQueryItem>& queryItemSnapshots);
   std::optional<RaycastHit> nearestRayIntersect(const std::vector<AABBQueryItem>& queryItemSnapshots,AABB_ADT::Ray ray);
}
