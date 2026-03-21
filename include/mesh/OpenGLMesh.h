#pragma once
#include "mesh/OpenGLMesh.h"


namespace MESH {
    class OpenGLMesh : public IMeshGpu {
    private:
        uint32_t vao=0, vbo=0, ebo=0, indexCount = 0;
    public:
        IMeshGpu* upload(const IMesh& mesh) override;
        void draw()= 0 override;
        ~OpenGLMesh() override;
        OpenGLMesh(const IMesh& mesh);
    };
}