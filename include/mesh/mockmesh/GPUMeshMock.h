#pragma once
#include "../IMeshGpu.h"

namespace MESH{
class GPUMeshMock : public IMeshGpu {

public:
    IMeshGpu* upload(const IMesh& mesh) override{}
    void draw() override{}

};
}