#pragma once
#include "math/Vec.h"
#include "math/Mat4.h"
#include <string>

namespace Engine {
    class Shader {

    public:
        unsigned int ID;
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        void use() const;

        // Uniforms
        void setMat4(const std::string& name, const Math::Mat4& mat) const;
        void setVec3(const std::string& name, const Math::Vec3& vec3) const;
        void setFloat(const std::string& name, float v) const;

    };
}
