#pragma once

namespace Game {

 
    void InitEnemies();                  
  
    void UpdateEnemies(float deltaTime);  
   
    void RenderEnemies();                

   
    int GetHealth(int enemyID);
    void TakeDamage(int enemyID, int amount);

    // Position
    float GetX(int enemyID);
    float GetY(int enemyID);
    float GetZ(int enemyID);
    void SetPosition(int enemyID, float x, float y, float z);

    
    void FireWeapon(int enemyID);

}
