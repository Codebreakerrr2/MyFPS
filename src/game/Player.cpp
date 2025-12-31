#include "game/Player.h"

#include <algorithm>

#include "engine/Input.h"
#include "engine/Physics.h"
#include "world/Map.h"

namespace Game {

    Player::playerID Player::nextID = 0;

    Player::Player() {
        id = nextID++;
    }

    void Player::Init(const Math::Vec3& startPos, Engine::Entity* entity, Physics::PhysicsBody* bodyy) {
        playerEntity = entity;
        body =bodyy;
        position = startPos;
        body->position = startPos;
        playerEntity->transform.position = position;
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
        Math::Vec3 wish(0.0f);

        Math::Vec3 forward(std::cos(yaw), 0, std::sin(yaw));
        Math::Vec3 right = Math::Normalize(Math::Cross(forward, {0,1,0}));

        // Bewegung basierend auf Input
        if (Engine::IsKeyPressed(GLFW_KEY_W)) wish = wish + forward;
        if (Engine::IsKeyPressed(GLFW_KEY_S)) wish = wish - forward;
        if (Engine::IsKeyPressed(GLFW_KEY_D)) wish = wish + right;
        if (Engine::IsKeyPressed(GLFW_KEY_A)) wish = wish - right;

        // Normalize nur, wenn überhaupt Richtung gedrückt wird
        if (Math::Length(wish) > 0.0f)
            wish = Math::Normalize(wish);

        // ---- Temporäre MaxSpeed für Sprint ----
        float maxSpeed = playerSpeed;
        if (Engine::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
            maxSpeed *= 2.0f;

        // ---- Acceleration ----
        float currentSpeed = Math::Dot(body->velocity, wish);
        float addSpeed = maxSpeed - currentSpeed;
        if (addSpeed > 0.0f && Math::Length(wish) > 0.0f) {
            float accelSpeed = body->accelerationRate * dt;
            if (accelSpeed > addSpeed)
                accelSpeed = addSpeed;
            body->velocity = body->velocity + wish * accelSpeed;
        }
        body->velocity = body->velocity * std::max(0.0f, 1.0f - body->friction * dt);
        body->position = body->position + body->velocity * dt;
    }


    void Player::UpdateTransform() {
        Physics::syncEntityToBodyPostion(body,playerEntity);
        position =playerEntity->transform.position ;
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
