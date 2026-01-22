#pragma once

#include "engine/Camera.h"
#include "engine/CameraController.h"
#include "engine/Entity.h"
#include "engine/PhysicsBody.h"
#include "math/Vec.h"

namespace Game {

    class Player {
        using playerID = unsigned int;

    public:
        Player();

        void Init(const Math::Vec3& startPos, Engine::Entity* entity,Physics::PhysicsBody* body);
        void Update(float deltaTime);
        Math::Vec3 GetForward() const;

    private:
        void UpdateLook(float dt);


        void UpdateMovement(float dt);
        void UpdateTransform();
        void UpdateCamera();

    public:
        [[nodiscard]] Math::Vec3 GetPosition() const {
            return position;
        }


        [[nodiscard]] float GetHeight() const {
            return height;
        }

        [[nodiscard]] float GetPitch() const {
            return pitch;
        }

        [[nodiscard]] float GetYaw() const {
            return yaw;
        }

    private:
        Physics::PhysicsBody* body;
        Engine::Entity* playerEntity = nullptr;

        Math::Vec3 position{0.0f};
        float height = 5.5f;
        // movment and looking
        float pitch = 0.0f;
        float yaw = 0.0f;
        float playerSpeed = 5.0f;

        playerID id;
        static playerID nextID;
    };

}
