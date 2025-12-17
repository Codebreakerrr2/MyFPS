#pragma once
#include <string>

namespace Game {


    struct Player {
        float x,y,z;
        int meshID;
    }

    extern Player player;

 
    void InitPlayer();                 
  
    void UpdatePlayer(float deltaTime); 

    void RenderPlayer();                

   
    int GetHealth();
    void TakeDamage(int amount);

   
    void FireWeapon();                  
    void ReloadWeapon();                

    // Position / Kamera
    float GetX();
    float GetY();
    float GetZ();
    void SetPosition(float x, float y, float z);

}
