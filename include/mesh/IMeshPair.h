#pragma once
#include <memory>

#include "IMesh.h"
#include "IMeshGpu.h"

namespace MESH {
    class IMeshPair {

    protected:
        std::unique_ptr<IMesh> mesh;
       mutable std::unique_ptr<IMeshGpu> gpuMesh;
        IMeshPair(std::unique_ptr<IMesh>&& mesh):mesh(std::move(mesh)){}
    public:
        virtual ~IMeshPair() = default;
      IMesh* getMesh() {
            return mesh.get();a
        }
        virtual   IMeshGpu* getGpuMesh() const  = 0;

    };
}