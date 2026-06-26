#include "AABB/AABB_ADT.h"


namespace Physics::AABB_ADT {
    AABB calcAABB(const std::vector<MESH::Vertex> &vertices) {
    }

AABB transform(const AABB &aabb, const Math::Mat4 &model) {
    }

    bool intersects(const AABB &aabb1, const AABB &aabb2) {
    }

    std::optional<float> intersects(const Ray &ray, const AABB &aabb) {
    }
}