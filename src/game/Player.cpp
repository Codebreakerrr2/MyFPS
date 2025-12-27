#include "game/Player.h"

#include <algorithm>

#include "engine/Input.h"
#include "world/Map.h"

namespace Game {

    Player::playerID Player::nextID = 0;

    Player::Player() {
        id = nextID++;
    }

    void Player::Init(const Math::Vec3& startPos, Engine::Entity* entity) {
        playerEntity = entity;

        // Player-Position
        position = startPos;
        playerEntity->transform.position = position;

        // Camera über Spieler platzieren
        camera.position = position;
        camera.position.y += height;

    }

    void Player::UpdateLook(float dt) {
        int dx, dy;
        Engine::GetMouseDelta(dx, dy);
        float sens = Engine::getMouseSensitivity();
        yaw += dx * sens;
        pitch -= dy * sens;
        pitch = std::clamp(pitch, -1.5f, 1.5f);
    }

    void Player::UpdateMovement(float dt) {
        Math::Vec3 forwardMove = Math::Normalize(Math::Vec3(std::cos(yaw),0.0f,std::sin(yaw)));
        Math::Vec3 rightMove = Math::Normalize(Math::Cross(forwardMove, Math::Vec3(0.0f, 1.0f, 0.0f)));
        if (Engine::IsKeyPressed(GLFW_KEY_W))
            position =position + forwardMove * playerSpeed * dt;
        if (Engine::IsKeyPressed(GLFW_KEY_S))
            position = position -forwardMove * playerSpeed * dt;
        if (Engine::IsKeyPressed(GLFW_KEY_D))
            position =  position +rightMove * playerSpeed * dt;
        if (Engine::IsKeyPressed(GLFW_KEY_A))
            position = position -rightMove * playerSpeed * dt;
    }

    void Player::UpdateTransform() {
        playerEntity->transform.position = position;
        playerEntity->transform.rotation.y=-yaw;
    }

    void Player::UpdateCamera() {
        camera.Rotate(pitch, yaw);
        camera.position = position;
        camera.position.y += height;
    }

    void Player::Update(float deltaTime) {
        Player::UpdateLook(deltaTime);
        Player::UpdateMovement(deltaTime);
        Player::UpdateTransform();
        Player::UpdateCamera();

    }

}
