#include "renderer/OpenGLRenderer.h"
#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "asset_manager/Registery.h"
#include "asset_manager/RenderBuffer.h"
#include "asset_manager/Types.h"
#include "camera/Camera.h"
#include "mesh/IMeshPair.h"
#include "renderer/Viewport.h"
#include "shader/IShader.h"
#include "window/IWindow.h"

namespace Renderer {

bool OpenGLRenderer::init(Window::IWindow* window) {
    this->window = window;
    GLFWwindow* glfwWindow =
        static_cast<GLFWwindow*>(window->getNativeHandle());
    if (!glfwWindow) {
        throw std::runtime_error("Invalid GLFW window handle");
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    int width, height;
    window->getSize(width, height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    LOG_SUCCESS("OpenGLRenderer initialized!");
    return true;
}
    void OpenGLRenderer::clear(float r, float g, float b, float a)  {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}




  void OpenGLRenderer::setViewPort(Viewport& vp){
                 glViewport(vp.getX(),vp.getY(),vp.getWidth(),vp.getHeight());
        }
         void OpenGLRenderer::setScissor(Viewport& vp) {
                  glScissor(vp.getX(), vp.getY(), vp.getWidth(), vp.getHeight());
        }
           void OpenGLRenderer::enableScissor(){
            glEnable(GL_SCISSOR_TEST);
           }
         void OpenGLRenderer::disableScissor(){
            glDisable(GL_SCISSOR_TEST);
         }





    void OpenGLRenderer::drawTriangle(Asset::Types::RenderBuffer& buffer,const Camera::Camera& camera) {



                auto* drawCommands = buffer.getBuffer();
    LOG_DEBUG("got the buffer");
                SHADER::IShader* currentShader = nullptr;
                MESH::IMeshPair* currentMesh = nullptr;

                for(const drawCommand& cd : *drawCommands ){
                    //Shader

                    if(currentShader != cd.shader){ 
                        currentShader = cd.shader;
                        if(currentShader == nullptr){ LOG_ERROR("shader of the renderable entity is not set, PROGRAM MIGHT CRASH!");
                            continue;
                        }

                        currentShader->use();

                }
                    currentShader->setMat4("u_model",cd.trans.GetModelMatrix());
                    currentShader->setMat4("u_view",camera.GetViewMatrix());
                    currentShader->setMat4("u_proj",camera.GetProjectionMatrix());
                    // naja eventuell roughness etc aus mateiral noch einbinden aber dafür kein shader datei erstmal

                    if(currentMesh != cd.drawCmdMeshTupel){
                        currentMesh = cd.drawCmdMeshTupel;
                        if(currentMesh == nullptr){ LOG_ERROR("mesh of renderable enitty is not set, PROGRAM MIGHT CRASH!");
                            continue;
                        }

                    }
                    currentMesh->getGpuMesh()->draw();
                }
    }
}
