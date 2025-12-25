#include "engine/parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace Engine {

    struct Vertex {
        float x, y, z;
    };

    bool LoadOBJ(const std::string& path, std::vector<float>& outVertices, std::vector<uint32_t>& outIndices) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Fehler: Konnte OBJ-Datei nicht öffnen: " << path << "\n";
            return false;
        }

        std::vector<Vertex> tempVertices;

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string prefix;
            ss >> prefix;

            if (prefix == "v") {
                Vertex v;
                ss >> v.x >> v.y >> v.z;
                tempVertices.push_back(v);
            } else if (prefix == "f") {
                uint32_t a, b, c;
                char slash; // um Textur/Normalen zu ignorieren
                std::string part;

                // Liest nur die erste Zahl jeder Face-Komponente (v/vt/vn)
                for (int i = 0; i < 3; ++i) {
                    ss >> part;
                    std::stringstream ps(part);
                    ps >> a;
                    if (i == 0) outIndices.push_back(a - 1);
                    else if (i == 1) outIndices.push_back(a - 1);
                    else if (i == 2) outIndices.push_back(a - 1);
                }
            }
        }

        // Flatten vertices
        for (auto& v : tempVertices) {
            outVertices.push_back(v.x);
            outVertices.push_back(v.y);
            outVertices.push_back(v.z);
        }

        return true;
    }

}
