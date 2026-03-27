#pragma once
#include <cstdint>
#include "mesh/IMeshGpu.h"


namespace MESH {
    class OpenGLMesh : public IMeshGpu {
    private:
        uint32_t vao=0, vbo=0, ebo=0, indexCount = 0;
    public:
        IMeshGpu* upload(const IMesh& mesh) override;
        void draw() override;
        ~OpenGLMesh() override;
        OpenGLMesh(const IMesh& mesh);
    };
}