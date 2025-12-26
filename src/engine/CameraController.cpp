#include "engine/CameraController.h"

#include <algorithm>

#include "engine/Input.h"
namespace Engine {



    void CameraController::Update(Camera &camera, float deltaTime,MoveMode mode) {

        Math::Vec3 movement(0.0f);
        float velocity = deltaTime * speed;

        if (mode==MoveMode::Flying) {
            Math::Vec3 forwardMove = camera.front;
            Math::Vec3 rightMove = Math::Normalize(Cross(camera.front, camera.up));
            if (Engine::IsKeyPressed(GLFW_KEY_W))  movement = forwardMove+movement;
            if (Engine::IsKeyPressed(GLFW_KEY_S)) movement = movement-forwardMove;
            if (Engine::IsKeyPressed(GLFW_KEY_D)) movement = movement+rightMove;
            if (Engine::IsKeyPressed(GLFW_KEY_A)) movement = movement-rightMove;
        } else {
            Math::Vec3 flatFront =Normalize(Math::Vec3(camera.front.x, 0.0f, camera.front.z));
            Math::Vec3 right = Normalize(Cross(flatFront, Math::Vec3(0.0f, 1.0f, 0.0f)));

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

        if (Length(movement) > 0.0f)
            camera.Move(Normalize(movement)*velocity);


    }
}
