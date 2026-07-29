#pragma once
#include "AABB_ADT.h"
#include "renderer/IRenderer.h"

namespace Physics::AABBSystem {

    struct AABBComponent {
        AABB_ADT::AABB localAABB;
        AABB_ADT::AABB worldAABB;
        bool dirty  = true;
        AABBComponent() = default;
        explicit AABBComponent(const AABB_ADT::AABB& aabb): localAABB(aabb),worldAABB(aabb), dirty(true){};
        explicit AABBComponent(const MESH::IMesh& mesh) :localAABB(AABB_ADT::calcAABB(mesh.getVertices())),worldAABB(localAABB),dirty(true){}

    };
    struct AABBQueryItem {
        Asset::Types::Entity entity;
        AABB_ADT::AABB worldAABB;
    };

    struct CollisionEvent {
        Asset::Types::Entity entity1;
        Asset::Types::Entity entity2;
        CollisionEvent(Asset::Types::Entity entity1, Asset::Types::Entity entity2):entity1(entity1),entity2(entity2){}
    };

    struct RaycastHit {
        Asset::Types::Entity entity;
        Math::Vec3 intersection;
        AABB_ADT::Ray ray;
        float t;
    };

   std::vector<CollisionEvent> getCollisions(const std::vector<AABBQueryItem>& queryItemSnapshots);
   std::optional<RaycastHit> nearestRayIntersect(const std::vector<AABBQueryItem>& queryItemSnapshots,const AABB_ADT::Ray& ray);
}
