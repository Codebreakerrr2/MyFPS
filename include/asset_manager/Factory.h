#pragma once
#include <functional>
#include <memory>
#include <shader/OpenGLShader.h>

#include "mesh/CPUmesh.h"
#include "mesh/OpenGLMeshPair.h"
#include "mesh/mockmesh/MeshPairMock.h"
#include "shader/MockShader.h"

namespace Factory{


/*
 * Shader Factory functions
 */
inline auto mockShader = []()->std::unique_ptr<SHADER::IShader> {
    return std::make_unique<SHADER::shaderMock>();
};
inline auto basicShader = []()->std::unique_ptr<SHADER::IShader> {
    return std::make_unique<SHADER::OpenGLShader>("assets/shaders/basic.vert","assets/shaders/basic.frag");
};






//________________________________________________________________________________________________________________
/*
 *Mesh Factory functions
 */
inline auto mockMesh= []()->std::unique_ptr<MESH::IMeshPair> {
    return std::make_unique<MESH::MeshPairMock>(std::make_unique<MESH::CPUmesh>(std::vector<MESH::Vertex>{},std::vector<uint32_t>{}));
};
inline auto cubeMesh = []()->std::unique_ptr<MESH::IMeshPair> {
    return std::make_unique<MESH::OpenGLMeshPair>(
        std::make_unique<MESH::CPUmesh>(
            std::vector<MESH::Vertex>{
                // Front
                {{-0.5f,-0.5f, 0.5f}, {0,0,1}, {0,0}},
                {{ 0.5f,-0.5f, 0.5f}, {0,0,1}, {1,0}},
                {{ 0.5f, 0.5f, 0.5f}, {0,0,1}, {1,1}},
                {{-0.5f, 0.5f, 0.5f}, {0,0,1}, {0,1}},

                // Back
                {{-0.5f,-0.5f,-0.5f}, {0,0,-1}, {1,0}},
                {{ 0.5f,-0.5f,-0.5f}, {0,0,-1}, {0,0}},
                {{ 0.5f, 0.5f,-0.5f}, {0,0,-1}, {0,1}},
                {{-0.5f, 0.5f,-0.5f}, {0,0,-1}, {1,1}},

                // Left
                {{-0.5f,-0.5f,-0.5f}, {-1,0,0}, {0,0}},
                {{-0.5f,-0.5f, 0.5f}, {-1,0,0}, {1,0}},
                {{-0.5f, 0.5f, 0.5f}, {-1,0,0}, {1,1}},
                {{-0.5f, 0.5f,-0.5f}, {-1,0,0}, {0,1}},

                // Right
                {{ 0.5f,-0.5f,-0.5f}, {1,0,0}, {1,0}},
                {{ 0.5f,-0.5f, 0.5f}, {1,0,0}, {0,0}},
                {{ 0.5f, 0.5f, 0.5f}, {1,0,0}, {0,1}},
                {{ 0.5f, 0.5f,-0.5f}, {1,0,0}, {1,1}},

                // Top
                {{-0.5f, 0.5f,-0.5f}, {0,1,0}, {0,1}},
                {{-0.5f, 0.5f, 0.5f}, {0,1,0}, {0,0}},
                {{ 0.5f, 0.5f, 0.5f}, {0,1,0}, {1,0}},
                {{ 0.5f, 0.5f,-0.5f}, {0,1,0}, {1,1}},

                // Bottom
                {{-0.5f,-0.5f,-0.5f}, {0,-1,0}, {1,1}},
                {{-0.5f,-0.5f, 0.5f}, {0,-1,0}, {1,0}},
                {{ 0.5f,-0.5f, 0.5f}, {0,-1,0}, {0,0}},
                {{ 0.5f,-0.5f,-0.5f}, {0,-1,0}, {0,1}},
            },
            std::vector<uint32_t>{
                0,1,2, 2,3,0,       // Front
                4,5,6, 6,7,4,       // Back
                8,9,10, 10,11,8,    // Left
                12,13,14, 14,15,12, // Right
                16,17,18, 18,19,16, // Top
                20,21,22, 22,23,20  // Bottom
            }
        )
    );
};
};

