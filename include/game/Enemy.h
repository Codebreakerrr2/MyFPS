#pragma once
#include <vector>

namespace Game {

    struct Enemy {
        float x, y, z;
        int health;
        int meshID;
    };

    extern std::vector<Enemy> enemies;

    void InitEnemies();
    void UpdateEnemies(float deltaTime);
    void RenderEnemies();
    void TakeDamage(size_t enemyIndex, int amount);
}
