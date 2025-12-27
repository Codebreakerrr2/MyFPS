#pragma once

#include "engine/Camera.h"
#include "engine/CameraController.h"
#include "engine/Entity.h"
#include "math/Vec.h"

namespace Game {

    class Player {
        using playerID = unsigned int;

    public:
        Player();

        void Init(const Math::Vec3& startPos, Engine::Entity* entity);
        void Update(float deltaTime);

      [[nodiscard]] const Engine::Camera& GetCamera() const { return camera; }

    private:
        void UpdateLook(float dt);
        void UpdateMovement(float dt);
        void UpdateTransform();
        void UpdateCamera();

        Engine::Camera camera;
        Engine::CameraController controller;
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
