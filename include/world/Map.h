#pragma once
#include <string>

namespace Game {


    bool LoadMap(const std::string& path);

    // Update pro Frame (falls z.B. bewegliche Objekte, Türen)
    void UpdateMap(float deltaTime);

    void RenderMap();

    // Abfragen, ob Spieler/Gegner auf einem festen Objekt stehen (für Physics/Kollision)
    bool IsSolid(float x, float y, float z);

}
