#include "Game/Player.h"
#include "engine/Input.h"
#include "engine/Physics.h"
#include "engine/Renderer.h"

namespace Game {

    Player player;

    // Initialisierung des Players
    void InitPlayer() {
        player.x = 0.0f;
        player.y = 0.0f;
        player.z = 0.0f;
        player.meshID = 0;   // z.B. Default Mesh
        player.health = 100;
    }

    // Update pro Frame
    void UpdatePlayer(float deltaTime) {
        // Movement
        float speed = 5.0f * deltaTime;

        if (Engine::IsKeyPressed('W')) player.z += speed;
        if (Engine::IsKeyPressed('S')) player.z -= speed;
        if (Engine::IsKeyPressed('A')) player.x -= speed;
        if (Engine::IsKeyPressed('D')) player.x += speed;

        // Gravity / Physics
        //Engine::UpdatePhysics(deltaTime);
    }

    // Render Player
    void RenderPlayer() {

    }

    // Health
    int GetHealth() {
        return player.health;
    }

    void TakeDamage(int amount) {
        player.health -= amount;
        if (player.health < 0) player.health = 0;
    }

    // Waffen
    void FireWeapon() {
        // TODO: Implement Fire Logic
    }

    void ReloadWeapon() {
        // TODO: Implement Reload Logic
    }

    // Position / Kamera
    float GetX() { return player.x; }
    float GetY() { return player.y; }
    float GetZ() { return player.z; }

    void SetPosition(float x, float y, float z) {
        player.x = x;
        player.y = y;
        player.z = z;
    }

} // namespace Game
