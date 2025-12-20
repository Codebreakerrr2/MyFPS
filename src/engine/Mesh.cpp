#include "engine/Mesh.h"
#include "glad/glad.h"
#include <iostream>

namespace Engine {

    static std::unordered_map<MeshID, Mesh> meshes;
    static MeshID nextMeshID = 1; // 0 = invalid

    MeshID LoadMesh(const std::vector<float>& vertices, uint32_t vertexStride)
    {
        Mesh mesh;
        glGenVertexArrays(1, &mesh.VAO);
        glGenBuffers(1, &mesh.VBO);

        glBindVertexArray(mesh.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, vertexStride, GL_FLOAT, GL_FALSE, vertexStride * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        mesh.vertexCount = vertices.size() / vertexStride;

        glBindVertexArray(0);


        MeshID id = nextMeshID++;
        meshes[id] = mesh;
        return id;
    }

    const Mesh* GetMesh(MeshID id)
    {
        auto it = meshes.find(id);
        if (it == meshes.end())
            return nullptr;

        return &it->second;
    }

    void ShutdownMeshes()
    {
        for (auto& [id, mesh] : meshes) {
            if (mesh.EBO) glDeleteBuffers(1, &mesh.EBO);
            if (mesh.VBO) glDeleteBuffers(1, &mesh.VBO);
            if (mesh.VAO) glDeleteVertexArrays(1, &mesh.VAO);
        }
        meshes.clear();
    }

}
