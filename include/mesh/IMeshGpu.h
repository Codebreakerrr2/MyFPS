#pragma once


namespace MES {
    class IMeshGpu {

    public:
    virtual ~IMeshGpu();
        virtual IMeshGpu* upload(const IMesh& mesh) = 0;
        virtual void draw()= 0;

    };
}