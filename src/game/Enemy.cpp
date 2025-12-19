#include "game/Enemy.h"
#include "engine/Physics.h"
#include "engine/Renderer.h"

namespace Game {

    std::vector<Enemy> enemies;

    void InitEnemies() {
        enemies.clear();
        // Beispiel: 3 Gegner an festen Positionen
        enemies.push_back({5.0f, 0.0f, 5.0f, 50, 2});
        enemies.push_back({-5.0f, 0.0f, 5.0f, 50, 3});
        enemies.push_back({0.0f, 0.0f, 10.0f, 50, 4});
    }

    void UpdateEnemies(float deltaTime) {
        float speed = 2.0f;
        for (auto& enemy : enemies) {
            // Bewegung auf X-Achse
            enemy.x += speed * deltaTime;

            // Ping-Pong-Bewegung
            if (enemy.x > 10.0f) {
                enemy.x = 10.0f;
                speed = -speed;
            } else if (enemy.x < -10.0f) {
                enemy.x = -10.0f;
                speed = -speed;
            }
        }
       // Engine::UpdatePhysics(deltaTime);
    }

    void RenderEnemies() {
    }

    void TakeDamage(size_t enemyIndex, int amount) {
    }
}
