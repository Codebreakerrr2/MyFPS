#pragma once
#include <string>

namespace Game {

 
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
