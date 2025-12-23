#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

namespace Engine {

    using MeshID = uint32_t;

    struct Mesh {
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int EBO = 0;      // optional (0 = nicht benutzt)
        uint32_t vertexCount = 0;
        int indexCount = 0;
        bool indexed = false;
    };

    // Mesh-System API
    MeshID LoadMesh(
        const std::vector<float>& vertices,
        uint32_t vertexStrideFloats   // z.B. 3 für xyz, 6 für xyz+normal
    );
    MeshID LoadMeshIndexed(const std::vector<float>& vertices,
        uint32_t vertexStrideFloats,
        const std::vector<uint32_t>& indices);

    const Mesh* GetMesh(MeshID id);

    void ShutdownMeshes();

}
