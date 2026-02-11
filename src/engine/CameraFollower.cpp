#include "engine/CameraFollower.h"
#include "game/Player.h"

namespace Camera {

    CameraFollower::CameraFollower(Game::Player* player, Engine::Camera* camera)
        : player(player), camera(camera) {}

    void CameraFollower::UpdateCamera() {
        if (!player || !camera) return;

        if (viewLook == FPS) {
            camera->Rotate(player->GetPitch(), player->GetYaw());
            camera->position = player->GetPosition();
            camera->position.y += height;

        }

        if (viewLook == THIRDPERSON) {
            Math::Vec3 desiredPos =
                player->GetPosition() - player->GetForward() * distance;
            desiredPos.y += height;

            camera->position = desiredPos;
            camera->front = Math::Normalize(
                player->GetPosition() - camera->position
            );
        }
    }

}
