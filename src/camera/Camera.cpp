#include "camera/Camera.h"
#include "math/Mat4.h"
#include <cmath> // für std::tan
namespace Engine {

    Camera mainCamera;







Camera::Camera(const Math::Vec3& pos, const Math::Vec3& target, const Math::Vec3& upVector)
    : position(pos), up(upVector) {
    front = Math::Normalize(target - pos);
}

Math::Mat4 Camera::GetViewMatrix() const {
    return Math::Mat4::LookAt(position, position + front, up);
}
    Math::Mat4 Camera::GetViewInverseMatrix() const
{
    return Math::Mat4::LookAtInverse(
        position,
        position + front,
        up
    );
}

Math::Mat4 Camera::GetProjectionMatrix() const {
    return Math::Mat4::Perspective(
        fov * 3.14159265f / 180.0f, // Grad → Radiant
        aspect,
        nearPlane,
        farPlane
    );
}
    Math::Mat4 Camera::GetProjectionInverseMatrix() const
{
    return Math::Mat4::PerspectiveInverse(
        fov * 3.14159265f / 180.0f,
        aspect,
        nearPlane,
        farPlane
    );
}


void Camera::Move(const Math::Vec3& delta) {
    position = position + delta;
}

void Camera::Rotate(float pitchRadians, float yawRadians) {
    // einfache Yaw-Pitch-Rotation
    Math::Vec3 direction;
    direction.x = std::cos(pitchRadians) * std::cos(yawRadians);
    direction.y = std::sin(pitchRadians);
    direction.z = std::cos(pitchRadians) * std::sin(yawRadians);
    front = Math::Normalize(direction);






}

void Camera::SetAspectRatio(float aspectRatio) {
    aspect = aspectRatio;

}
}
