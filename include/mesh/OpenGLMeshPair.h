#pragma once
#include "IMeshPair.h"
#include "OpenGLMesh.h"

namespace MESH {
    class OpenGLMeshPair : public IMeshPair {

    public:
        OpenGLMeshPair(std::unique_ptr<IMesh>&& mesh): IMeshPair(std::move(mesh)) {}

         IMeshGpu* getGpuMesh()const override {
            if (!gpuMesh) {
                gpuMesh = std::make_unique<OpenGLMesh>(*mesh);
            }
            return gpuMesh.get();
        }
    };
}
