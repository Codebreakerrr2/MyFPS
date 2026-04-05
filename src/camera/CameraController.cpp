#include "camera/CameraController.h"
#include "input/IInput.h"

void Camera::CameraController::update(Camera &camera, float deltaTime, MoveMode mode) {

    updateRotation(camera, deltaTime);

    Math::Vec3 moveDirection = getMoveDirection(camera,mode);
    float velocity = speed*deltaTime;
    camera.move(moveDirection*velocity);

}

Math::Vec3 Camera::CameraController::getMoveDirection(const Camera &camera, MoveMode mode) {
    Math::Vec3 moveDirection(0.0f, 0.0f, 0.0f);

    Math::Vec3 forward = Math::Normalize(camera.front);
    Math::Vec3 right   = Math::Normalize(Math::Cross(forward, camera.up));

    if (mode == MoveMode::Player)
        forward.y = 0.0f; // keine vertikale Bewegung im Player Mode


    float keyboardForward = inputKeyBoard ? inputKeyBoard->GetAxis(Input::Action::Forward) : 0.0f;
    float keyboardRight   = inputKeyBoard ? inputKeyBoard->GetAxis(Input::Action::Right)   : 0.0f;


    float xBOXForward = inputXBOX ? inputXBOX->GetAxis(Input::Action::Forward) : 0.0f;
    float xBOXRight   = inputXBOX ? inputXBOX->GetAxis(Input::Action::Right)   : 0.0f;


    moveDirection = moveDirection +(forward * (keyboardForward + xBOXForward));
    moveDirection = moveDirection +(right   * (keyboardRight   + xBOXRight));

    if (Math::Length(moveDirection) > 0.0f)
        moveDirection = Math::Normalize(moveDirection);

    return moveDirection;
}

void Camera::CameraController::updateRotation(Camera &camera, float deltaTime) {
    // 🔹 Maus direkt updaten
    if(inputMouse)
        inputMouse->Update();
    // 🔹 Maus (Delta, KEIN deltaTime!)
    float mouseDX = inputMouse ? inputMouse->GetMouseDeltaX() : 0.0f;
    float mouseDY = inputMouse ? inputMouse->GetMouseDeltaY() : 0.0f;

    // 🔹 XBOX Stick (Zustand, MIT deltaTime!)
    float stickX = inputXBOX ?
        (inputXBOX->GetAxis(Input::Action::LookRight) -
         inputXBOX->GetAxis(Input::Action::LookLeft)) : 0.0f;

    float stickY = inputXBOX ?
        (inputXBOX->GetAxis(Input::Action::LookUp) -
         inputXBOX->GetAxis(Input::Action::LookDown)) : 0.0f;

    // 🔹 kombinieren
    float dx = mouseDX + stickX * deltaTime * 100.0f; // 100 = Stick-Sensitivity
    float dy = mouseDY + stickY * deltaTime * 100.0f;

    // 🔹 Rotation anwenden
    yaw   += dx * MouseSensitivity;
    pitch += dy * MouseSensitivity;

    // 🔹 Pitch clamp (kein Umkippen)
    const float limit = 89.0f * 3.14159265f / 180.0f;

    if (pitch > limit) pitch = limit;
    if (pitch < -limit) pitch = -limit;

    // 🔹 Kamera rotieren
    camera.rotate(pitch, yaw);
}
