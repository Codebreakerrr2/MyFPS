#pragma once
#include "math/Vec.h"
#include <cstdint>
#include <vector>
namespace MESH {

    struct Vertex {
       Math::Vec3 Position;
        Math::Vec3 Normal;
        Math::Vec2 uv;

    };

    class IMesh {

        virtual ~IMesh() = default;
        virtual void set(const std::vector<Vertex>& vertices) = 0;
        virtual const std::vector<Vertex>& get() const = 0;
        virtual void set(const std::vector<uint32_t>& indices) = 0;
        virtual const std::vector<uint32_t>& getIndices() const = 0;
    };
}