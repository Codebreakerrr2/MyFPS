#pragma once
#include "engine/IShader.h"
namespace Engine {


     class OpenGLShader : public IShader {
        public:
         unsigned int ID;

         OpenGLShader(const char* vertexPath,
                      const char* fragmentPath) ;

         ~OpenGLShader() override;

         void use() const override;

         void setMat4(const std::string& name,
                      const Math::Mat4& mat) const override;

         void setVec3(const std::string& name,
                      const Math::Vec3& vec3) const override;

         void setFloat(const std::string& name,
                       float v) const override;

         void setBool(const std::string& name,
                      bool v) const override;

 
     };


}