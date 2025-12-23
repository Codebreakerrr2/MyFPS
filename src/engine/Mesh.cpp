#include "engine/Mesh.h"
#include "glad/glad.h"
#include <iostream>

namespace Engine {
    static std::unordered_map<MeshID, Mesh> meshes;
    static MeshID nextMeshID = 1; // 0 = invalid


    //REDUNDANT MESHLOAD EVENTUELL LÖSCHEN
    MeshID LoadMesh(const std::vector<float> &vertices, uint32_t vertexStride) {
        Mesh mesh;
        glGenVertexArrays(1, &mesh.VAO);
        glGenBuffers(1, &mesh.VBO);
        glGenBuffers(1, &mesh.EBO);


        glBindVertexArray(mesh.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, vertexStride, GL_FLOAT, GL_FALSE, vertexStride * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        mesh.vertexCount = vertices.size() / vertexStride;

        glBindVertexArray(0);


        MeshID id = nextMeshID++;
        meshes[id] = mesh;
        return id;
    }


    //REDUNDANT MESHLOAD EVENTUELL LÖSCHEN
    MeshID LoadMeshIndexed(
        const std::vector<float> &vertices,
        uint32_t vertexStride,
        const std::vector<uint32_t> &indices
    ) {
        Mesh mesh{};
        mesh.indexed = true;
        mesh.vertexCount = vertices.size() / vertexStride;
        mesh.indexCount = indices.size();

        glGenVertexArrays(1, &mesh.VAO);
        glGenBuffers(1, &mesh.VBO);
        glGenBuffers(1, &mesh.EBO);

        glBindVertexArray(mesh.VAO);

        // ---------- VBO ----------
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),vertices.data(),GL_STATIC_DRAW);

        // ---------- EBO ----------
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(uint32_t),indices.data(),GL_STATIC_DRAW);

        // ---------- Vertex Layout ----------
        glVertexAttribPointer(0,vertexStride,GL_FLOAT,GL_FALSE,vertexStride * sizeof(float),(void *) 0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        MeshID id = nextMeshID++;
        meshes[id] = mesh;
        return id;
    }


    const Mesh *GetMesh(MeshID id) {
        auto it = meshes.find(id);
        if (it == meshes.end())
            return nullptr;

        return &it->second;
    }

    void ShutdownMeshes() {
        for (auto &[id, mesh]: meshes) {
            if (mesh.EBO)
                glDeleteBuffers(1, &mesh.EBO);
            if (mesh.VBO)
                glDeleteBuffers(1, &mesh.VBO);
            if (mesh.VAO)
                glDeleteVertexArrays(1, &mesh.VAO);
        }
        meshes.clear();
    }
}
