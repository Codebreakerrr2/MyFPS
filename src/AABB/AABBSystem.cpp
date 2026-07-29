#include "physics/AABB/AABBSystem.h"

namespace Physics::AABBSystem {

    std::vector<CollisionEvent> getCollisions(const std::vector<AABBQueryItem>& queryItemSnapshots) {

        std::vector<CollisionEvent> collisionEvents;

      for (size_t i = 0; i < queryItemSnapshots.size(); i++) {
          for (size_t j = i+1; j < queryItemSnapshots.size() ; ++j) {
              const auto& item1 = queryItemSnapshots[i];
              const auto& item2 = queryItemSnapshots[j];

              if (AABB_ADT::intersects(item1.worldAABB, item2.worldAABB)) {
                  collisionEvents.emplace_back(item1.entity, item2.entity);
              }

          }
      }
        return collisionEvents;
    }

    std::optional<RaycastHit> nearestRayIntersect(
     const std::vector<AABBQueryItem>& queryItemSnapshots,
     const AABB_ADT::Ray& ray)
    {
        std::optional<RaycastHit> nearestHit;
        float nearestT = std::numeric_limits<float>::max();

        for (const auto& queryItem : queryItemSnapshots) {
            const auto hitT =
                AABB_ADT::intersects(ray, queryItem.worldAABB);

            if (!hitT.has_value()) {
                continue;
            }

            if (*hitT >= nearestT) {
                continue;
            }

            nearestT = *hitT;

            nearestHit = RaycastHit{
                .entity = queryItem.entity,
                .intersection =
                    ray.origin + ray.direction * nearestT,
                .ray = ray,
                .t = nearestT,
            };
        }

        return nearestHit;
    }
}
