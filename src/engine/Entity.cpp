// engine/Entity.cpp
#include "engine/Entity.h"

Math::Mat4 Engine::Transform::GetModelMatrix() const {
    return Math::Mat4::Translation(position) *
           Math::Mat4::RotationX(rotation.x) *
           Math::Mat4::RotationY(rotation.y) *
           Math::Mat4::RotationZ(rotation.z) *
           Math::Mat4::Scale(scale);
}


