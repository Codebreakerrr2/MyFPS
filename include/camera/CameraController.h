#pragma once
#include "engine/Camera.h"



namespace Engine {
    enum class MoveMode {Flying, Player };
    class CameraController {
    public:
        void Update(Camera& camera, float deltaTime,MoveMode mode);

        Math::Vec3 GetMoveDirection(const Camera &camera, MoveMode mode);

        void UpdateRotation(Camera &camera, float deltaTime);

        void SetSpeed(float s) { speed = s; }

    private:
        float speed = 3.0f;
        float yaw = 0.0f;
        float pitch = 0.0f;
        float MouseSensitivity = 0.004f;
    };


}