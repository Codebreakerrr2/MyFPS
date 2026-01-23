#pragma once
#include "Camera.h"
#include "Game/Player.h"

namespace Camera {

    enum CameraFollowerType { FPS, THIRDPERSON };

    class CameraFollower {
    public:
        CameraFollower(Game::Player* player, Engine::Camera* camera);

        void UpdateCamera();

        CameraFollowerType viewLook = FPS;

    private:
        Game::Player* player = nullptr;
        Engine::Camera* camera = nullptr;

        float height = 5.0f;
        float distance = 5.0f;
    };

}
