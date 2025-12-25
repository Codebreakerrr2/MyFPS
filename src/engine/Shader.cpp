#include "engine/Shader.h"
#include "math/Vec.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
namespace Engine {
    // -------- Hilfsfunktion: Datei lesen --------
    static std::string ReadShaderFile(const char* path)
    {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "ERROR: Could not open shader file: " << path << std::endl;
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    //  Shader kompilieren
    static unsigned int CompileShader(unsigned int type, const char* src)
    {
        unsigned int id = glCreateShader(type);
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            char info[512];
            glGetShaderInfoLog(id, 512, nullptr, info);
            std::cerr << "SHADER COMPILE ERROR:\n" << info << std::endl;
        }

        return id;
    }

    // -------- Konstruktor --------
    Shader::Shader(const char* vertexPath, const char* fragmentPath)
    {
        std::string vertCode = ReadShaderFile(vertexPath);
        std::string fragCode = ReadShaderFile(fragmentPath);

        unsigned int vert = CompileShader(GL_VERTEX_SHADER, vertCode.c_str());
        unsigned int frag = CompileShader(GL_FRAGMENT_SHADER, fragCode.c_str());

        ID = glCreateProgram();
        glAttachShader(ID, vert);
        glAttachShader(ID, frag);
        glLinkProgram(ID);

        int success;
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            char info[512];
            glGetProgramInfoLog(ID, 512, nullptr, info);
            std::cerr << "SHADER LINK ERROR:\n" << info << std::endl;
        }

        glDeleteShader(vert);
        glDeleteShader(frag);
    }

    // -------- Destruktor --------
    Shader::~Shader()
    {
        glDeleteProgram(ID);
    }


    void Shader::use() const
    {
        glUseProgram(ID);
    }

    // -------- Uniforms --------
    void Shader::setMat4(const std::string& name, const Math::Mat4& mat) const
    {
        int loc = glGetUniformLocation(ID, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, mat.m);
    }

    void Shader::setVec3(const std::string& name, const Math::Vec3& v) const {
        int loc = glGetUniformLocation(ID, name.c_str());
        glUniform3f(loc, v.x, v.y, v.z);
    }

    void Shader::setFloat(const std::string& name, float v) const
    {
        int loc = glGetUniformLocation(ID, name.c_str());
        glUniform1f(loc, v);
    }
}