#pragma once
#include "mesh\IMesh.h"



namespace MESH {
    class CPUmesh : public IMesh {
    private:
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

    public:
        CPUmesh(const std::vector<Vertex>& vert ,const std::vector<uint32_t>& ind)
            : vertices(vert), indices(ind) {}

        void set(const std::vector<Vertex>& vertices) override {
            this->vertices = vertices;
        }

        const std::vector<Vertex>& getVertices() const override {
            return vertices;
        }

        void set(const std::vector<uint32_t>& indices) override {
            this->indices = indices;
        }

        const std::vector<uint32_t>& getIndices() const override {
            return indices;
        }
    };
}