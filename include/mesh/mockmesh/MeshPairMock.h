#pragma once
#include "mesh/IMeshPair.h"

namespace MESH {
    class MeshPairMock :public IMeshPair {

    public:
        MeshPairMock(std::unique_ptr<IMesh>&& mesh): IMeshPair(std::move(mesh)) {}

        IMeshGpu* getGpuMesh()const override {
            return nullptr;
        }
    };
}