#pragma once
#include "mesh/IMesh.h"

namespace MESH {
    class IMeshGpu {

    public:
    virtual ~IMeshGpu() = default;
        virtual IMeshGpu* upload(const IMesh& mesh) = 0;
        virtual void draw()= 0;

    };
}