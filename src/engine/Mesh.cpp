#include "engine/Mesh.h"
#include "glad/glad.h"
#include <iostream>

namespace Engine {
    static std::unordered_map<MeshID, Mesh> meshes;
    static MeshID nextMeshID = 1; // 0 = invalid


    Geometry::AABB GetBoundingBox(const std::vector<float>& vertices) {
        if (vertices.size()%3!=0 || vertices.size() < 3) {
            return Geometry::AABB(Math::Vec3 (0),Math::Vec3(0));
        }

        Math::Vec3 min = Math::Vec3(vertices[0], vertices[1], vertices[2]);
        Math::Vec3 max = Math::Vec3(vertices[0], vertices[1], vertices[2]);

         for (int i = 3; i < vertices.size(); i+=3) {
             min.x = std::min(min.x, vertices[i]);
             min.y = std::min(min.y, vertices[i+1]);
             min.z = std::min(min.z, vertices[i+2]);
             max.x = std::max(max.x, vertices[i]);
             max.y = std::max(max.y, vertices[i+1]);
             max.z = std::max(max.z, vertices[i+2]);

         }
        return Geometry::AABB(min, max);
    }

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
        mesh.boundingBox = GetBoundingBox(vertices);

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

    //________________TEST FUNCTIONS_____________________
    MeshID LoadMeshTest(const std::vector<float>& vertices) {

        Mesh mesh{};
        mesh.indexed = true;
        mesh.boundingBox = GetBoundingBox(vertices);
        meshes[++nextMeshID] = mesh;
        return nextMeshID;

    }


}
