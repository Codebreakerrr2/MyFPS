#include "engine/CameraController.h"

#include <algorithm>

#include "engine/Input.h"
namespace Engine {



    void CameraController::Update(Camera &camera, float deltaTime,MoveMode mode) {
        float speedFactor = 1.0f;
        Math::Vec3 movement(0.0f);


        if (mode==MoveMode::Flying) {
            Math::Vec3 forwardMove = Math::Normalize(camera.front);
            Math::Vec3 rightMove = Math::Normalize(Cross(camera.front, camera.up));
            if (Engine::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) speedFactor = 5.0f;
            if (Engine::IsKeyPressed(GLFW_KEY_W))  movement = forwardMove+movement;
            if (Engine::IsKeyPressed(GLFW_KEY_S)) movement = movement-forwardMove;
            if (Engine::IsKeyPressed(GLFW_KEY_D)) movement = movement+rightMove;
            if (Engine::IsKeyPressed(GLFW_KEY_A)) movement = movement-rightMove;
        } else {
            Math::Vec3 flatFront =Normalize(Math::Vec3(camera.front.x, 0.0f, camera.front.z));
            Math::Vec3 right = Normalize(Cross(flatFront, Math::Vec3(0.0f, 1.0f, 0.0f)));
            if (Engine::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) speedFactor = 2.0f;
            if (Engine::IsKeyPressed(GLFW_KEY_W)) movement = movement+flatFront;
            if (Engine::IsKeyPressed(GLFW_KEY_S)) movement = movement-flatFront;
            if (Engine::IsKeyPressed(GLFW_KEY_D)) movement = movement+right;
            if (Engine::IsKeyPressed(GLFW_KEY_A)) movement = movement-right;

        }
        int dx, dy;
        Engine::GetMouseDelta(dx, dy);
        yaw   += dx * MouseSensitivity;
        pitch -= dy * MouseSensitivity;
        pitch = std::clamp(pitch, -1.5f, 1.5f);
        camera.Rotate(pitch, yaw);

        float velocity = deltaTime * speed*speedFactor;


        if (Length(movement) > 0.0f)
            camera.Move(Normalize(movement)*velocity);


    }
    Math::Vec3 CameraController::GetMoveDirection(
    const Camera& camera,
    MoveMode mode
) {
        Math::Vec3 movement(0.0f);

        if (mode == MoveMode::Player) {
            Math::Vec3 forward = Normalize(
                Math::Vec3(camera.front.x, 0.0f, camera.front.z)
            );
            Math::Vec3 right = Normalize(Cross(forward, Math::Vec3(0,1,0)));

            if (Engine::IsKeyPressed(GLFW_KEY_W)) movement =movement + forward;
            if (Engine::IsKeyPressed(GLFW_KEY_S)) movement = movement -forward;
            if (Engine::IsKeyPressed(GLFW_KEY_D)) movement = movement+ right;
            if (Engine::IsKeyPressed(GLFW_KEY_A)) movement = movement -right;
        }

        return movement;
    }
    void CameraController::UpdateRotation(Camera& camera, float deltaTime) {
        int dx, dy;
        Engine::GetMouseDelta(dx, dy);

        yaw   += dx * MouseSensitivity;
        pitch -= dy * MouseSensitivity;
        pitch = std::clamp(pitch, -1.5f, 1.5f);

        camera.Rotate(pitch, yaw);
    }


}
