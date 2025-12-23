#pragma once

#include <cstdint>
#include "engine/Mesh.h"

namespace Engine {

    using EntityID = uint32_t;

    // ---------------- Transform ----------------
    struct Transform {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        float rotX = 0.0f;
        float rotY = 0.0f;
        float rotZ = 0.0f;

        float scaleX = 1.0f;
        float scaleY = 1.0f;
        float scaleZ = 1.0f;
    };

    // ---------------- Material ----------------
    struct Material {
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        float a = 1.0f;
    };

    // ---------------- Entity ----------------
    struct Entity {
        EntityID id = 0;

        MeshID mesh = 0;
        Transform transform;
        Material material;
    };

}
