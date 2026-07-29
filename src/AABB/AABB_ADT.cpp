#include "physics/AABB/AABB_ADT.h"
#include <algorithm>



namespace Physics::AABB_ADT {
    AABB calcAABB(const std::vector<MESH::Vertex> &vertices) {
        Math::Vec3 Max(-FLT_MAX);
        Math::Vec3 Min(FLT_MAX);

        for (const auto& vert : vertices) {
            Max.x = std::max(Max.x,vert.Position.x);
            Max.y = std::max(Max.y,vert.Position.y);
            Max.z = std::max(Max.z,vert.Position.z);
            Min.x = std::min(Min.x,vert.Position.x);
            Min.y = std::min(Min.y,vert.Position.y);
            Min.z = std::min(Min.z,vert.Position.z);
        }
        return AABB{Min,Max};
    }

AABB transform(const AABB &aabb, const Math::Mat4 &model) {
        const Math::Vec3 corners[8] = {
            {aabb.min.x, aabb.min.y, aabb.min.z},
            {aabb.max.x, aabb.min.y, aabb.min.z},
            {aabb.min.x, aabb.max.y, aabb.min.z},
            {aabb.max.x, aabb.max.y, aabb.min.z},

            {aabb.min.x, aabb.min.y, aabb.max.z},
            {aabb.max.x, aabb.min.y, aabb.max.z},
            {aabb.min.x, aabb.max.y, aabb.max.z},
            {aabb.max.x, aabb.max.y, aabb.max.z}
        };
        Math::Vec4 transformed = model * Math::Vec4(corners[0].x,corners[0].y,corners[0].z,1.0f);
        AABB box{
        Math::Vec3(transformed.x,transformed.y,transformed.z),
            Math::Vec3(transformed.x,transformed.y,transformed.z)
        };

        for (const Math::Vec3& corner: corners) {
            Math::Vec4 transform = model * Math::Vec4(corner.x,corner.y,corner.z,1.0f);
            Math::Vec3 transformReduced = Math::Vec3(transform.x,transform.y,transform.z);

            box.max = Math::Max(box.max,transformReduced);
            box.min = Math::Min(box.min,transformReduced);
        }
        return box;


    }

    bool intersects(const AABB& aabb1, const AABB& aabb2)
    {
        if (aabb1.max.x < aabb2.min.x ||
            aabb1.min.x > aabb2.max.x)
        {
            return false;
        }

        if (aabb1.max.y < aabb2.min.y ||
            aabb1.min.y > aabb2.max.y)
        {
            return false;
        }

        if (aabb1.max.z < aabb2.min.z ||
            aabb1.min.z > aabb2.max.z)
        {
            return false;
        }

        return true;
    }

    std::optional<float> intersects(const Ray& ray, const AABB& aabb)
    {
        float tMin = 0.0f;
        float tMax = std::numeric_limits<float>::max();

        for (int axis = 0; axis < 3; ++axis) {
             float origin = ray.origin[axis];
             float direction = ray.direction[axis];
             float boxMin = aabb.min[axis];
             float boxMax = aabb.max[axis];

            if (std::abs(direction) < 0.000001f) {
                // Ray ist parallel zu den Flächen dieser Achse.
                if (origin < boxMin || origin > boxMax) {
                    return std::nullopt;
                }

                continue;
            }

            float t1 = (boxMin - origin) / direction;
            float t2 = (boxMax - origin) / direction;

            if (t1 > t2) {
                std::swap(t1, t2);
            }

            tMin = std::max(tMin, t1);
            tMax = std::min(tMax, t2);

            if (tMin > tMax) {
                return std::nullopt;
            }
        }

        return tMin;
    }
}
