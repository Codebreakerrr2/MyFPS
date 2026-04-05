
#pragma once
#include "camera/Camera.h"
#include "input/InputKeyboard.h"
#include "input/InputMouse.h"
#include "input/InputXBOX.h"


namespace Camera {
    enum class MoveMode {Flying, Player };
    class CameraController {
    public:
        CameraController(Input::InputKeyboard* keyboard, Input::InputXBOX* xbox,Input::InputMouse* mouse):inputKeyBoard(keyboard),inputXBOX(xbox),inputMouse(mouse){}
        void update(Camera& camera, float deltaTime,MoveMode mode);

        Math::Vec3 getMoveDirection(const Camera &camera, MoveMode mode);

        void updateRotation(Camera &camera, float deltaTime);

        void setSpeed(float s) { speed = s; }

    private:
        Input::InputKeyboard* inputKeyBoard;
        Input::InputXBOX* inputXBOX;
        Input::InputMouse* inputMouse;
        float speed = 3.0f;
        float yaw = 0.0f;
        float pitch = 0.0f;
        float MouseSensitivity = 0.004f;
    };


}
