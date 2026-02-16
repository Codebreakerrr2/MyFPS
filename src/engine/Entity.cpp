// engine/Entity.cpp
#include "engine/Entity.h"

#include <cfloat>

#include "engine/Mesh.h"

Math::Mat4 Engine::Transform::GetModelMatrix() const {
    return Math::Mat4::Translation(position) *
           Math::Mat4::RotationX(rotation.x) *
           Math::Mat4::RotationY(rotation.y) *
           Math::Mat4::RotationZ(rotation.z) *
           Math::Mat4::Scale(scale);
}

Geometry::AABB Engine::Entity::GetAABB() const {
    Geometry::AABB local = GetMesh(meshID)->boundingBox;
    Math::Mat4 model = transform.GetModelMatrix();

    Math::Vec3 min = Math::Vec3(FLT_MIN);
    Math::Vec3 max = Math::Vec3(-FLT_MAX);

    Math::Vec3 corners[8] = {
        {local.min.x, local.min.y, local.min.z},
        {local.max.x, local.min.y, local.min.z},
        {local.min.x, local.max.y, local.min.z},
        {local.max.x, local.max.y, local.min.z},
        {local.min.x, local.min.y, local.max.z},
        {local.max.x, local.min.y, local.max.z},
        {local.min.x, local.max.y, local.max.z},
        {local.max.x, local.max.y, local.max.z},
    };

    for (auto c: corners) {
        Math::Vec4 temp = model* Math::Vec4(c.x,c.y,c.z,1);
        Math::Vec3 transformed = Math::Vec3(temp.x, temp.y, temp.z);

        min = Min(min,transformed);
        max = Max(max,transformed);
    }
    return Geometry::AABB(min, max);

}

