#pragma once
#include <optional>
#include "asset_manager/Types.h"
#include "math/Vec.h"
#include "mesh/IMesh.h"


namespace Physics::AABB_ADT{

    struct AABB{
        Math::Vec3 min;
        Math::Vec3 max;
    };
    struct Ray {
        Math::Vec3 origin;
        Math::Vec3 direction;
    };

    AABB calcAABB(const std::vector<MESH::Vertex>& vertices);
    AABB transform(const AABB& aabb, const Math::Mat4& model);
    bool intersects(const AABB& aabb1, const AABB& aabb2);
    std::optional<float> intersects(const Ray& ray, const AABB& aabb);



    

};
