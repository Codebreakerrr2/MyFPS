#pragma once
#include "math/Vec.h"
#include "math/Mat4.h"
#include <string>

namespace Engine {
    class IShader {

    public:

        virtual ~IShader() = default;

        virtual void use() const = 0;

       

        // Uniforms
        virtual void setMat4(const std::string& name, const Math::Mat4& mat) const= 0;
        virtual void setVec3(const std::string& name, const Math::Vec3& vec3) const= 0;
        virtual void setFloat(const std::string& name, float v) const= 0;
        virtual void setBool(const std::string& name, bool v) const= 0;


    };
}