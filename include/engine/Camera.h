#pragma once
#include "math/Mat4.h"
#include "math/Vec.h"
namespace Engine{
class Camera {
public:
    // Position & Orientierung
    Math::Vec3 position {0.0f, 0.0f, 3.0f};
    Math::Vec3 front    {0.0f, 0.0f, -1.0f};
    Math::Vec3 up       {0.0f, 1.0f, 0.0f};

    // Perspektive
    float fov = 100.0f;          // Field of View in Grad
    float aspect = 16.0f / 9.0f;
    float nearPlane = 0.1f;
    float farPlane  = 30.0f;


    Camera() = default;
    Camera(const Math::Vec3& pos, const Math::Vec3& target, const Math::Vec3& upVector);


    Math::Mat4 GetViewMatrix() const;
    Math::Mat4 GetProjectionMatrix() const;


    void Move(const Math::Vec3& delta);
    void Rotate(float pitchRadians, float yawRadians);
};
}