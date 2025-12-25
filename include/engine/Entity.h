#pragma once

#include "Math/Vec.h"
#include "Math/Mat4.h"
#include "Engine/Shader.h"

namespace Engine {

    struct Transform {
        Math::Vec3 position {0.0f};
        Math::Vec3 rotation {0.0f};   // Euler (radians)
        Math::Vec3 scale    {1.0f};

        // Model-Matrix aus Position / Rotation / Scale
        Math::Mat4 GetModelMatrix() const;
    };


    struct Material {
        Shader* shader = nullptr;
        Math::Vec3 color {1.0f};
    };

    struct Entity {
        int meshID = -1;
        Transform transform;
        Material material;
    };

}
