#pragma once

#include "asset_manager/type.h"
#include "math/Vec.h"
#include "math/Mat4.h"
#include "Engine/Shader.h"
#include "geometry/Geometry.h"


namespace Engine {

    struct Transform {
        Math::Vec3 position {0.0f};
        Math::Vec3 rotation {0.0f};   // Euler (radians)
        Math::Vec3 scale    {1.0f};

        // Model-Matrix aus Position / Rotation / Scale
        Math::Mat4 GetModelMatrix() const;
    };


    struct Material {
        OpenGLShader* shader = nullptr;
        Math::Vec3 color {1.0f};
        Material() = default;
        Material(OpenGLShader* shader,Math::Vec3 color): shader(shader), color(color) {};
    };

    struct Entity {
        std::string name;
        Manager::EntityID id;
        int meshID = -1;
        Transform transform{};
        Material material{};
        Geometry::AABB GetAABB() const;
    };

}
