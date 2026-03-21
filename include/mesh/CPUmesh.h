#pragma once
#include "mesh\IMesh.h"



namespace MESH {
    class CPUmesh : public IMesh {
    private:
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

    public:
        CPUmesh(const std::vector<Vertex>& vert ,const std::vector<uint32_t>& ind):vertices(vert),indices(ind){}
         void set(const std::vector<Vertex>& vert){vertices = vert;}
         const std::vector<Vertex>& get() const {return vertices;}
         void set(const std::vector<uint32_t>& ind) {indices = ind;}
         const std::vector<uint32_t>& getIndices(){return indices;}
    };
}