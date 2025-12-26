#pragma once
#include "engine/Camera.h"



namespace Engine {
    enum class MoveMode {Flying, Player };
    class CameraController {
    public:
        void Update(Camera& camera, float deltaTime,MoveMode mode);

        void SetSpeed(float s) { speed = s; }

    private:
        float speed = 10.0f;
        float yaw = 0.0f;
        float pitch = 0.0f;
        float MouseSensitivity = 0.004f;
    };


}