#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace Engine {

    // Lädt eine OBJ-Datei (nur Vertex-Positionen & Indices)
    // vertices: flaches Array: x1,y1,z1,x2,y2,z2,...
    // indices: Indizes für glDrawElements
    bool LoadOBJ(const std::string& path, std::vector<float>& vertices, std::vector<uint32_t>& indices);

}
