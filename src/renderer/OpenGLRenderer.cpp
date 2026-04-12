#include "renderer/OpenGLRenderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "asset_manager/Types.h"
#include "asset_manager/Registery.h"
#include "camera/Camera.h"
#include "mesh/IMeshPair.h"
#include "renderer/Viewport.h"
#include "shader/IShader.h"
#include "window/IWindow.h"
#include "asset_manager/RenderBuffer.h"

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



     void OpenGLRenderer::addViewport(Viewport& viewport){
        viewports.emplace_back(&viewport);
        LOG_SUCCESS("Viewport "+ viewport.getName()+" added to viewport collection!");
    }

    void OpenGLRenderer::renderViewports(Asset::Types::RenderBuffer& buffer){
        glEnable(GL_SCISSOR_TEST);
        for(auto* vp: viewports){
            glViewport(vp->getX(),vp->getY(),vp->getWidth(),vp->getHeight());
            glScissor(vp->getX(), vp->getY(), vp->getWidth(), vp->getHeight());

            drawTriangle(buffer,*vp->getCamera());
        }
       glDisable(GL_SCISSOR_TEST);

    }



    void OpenGLRenderer::drawTriangle(Asset::Types::RenderBuffer& buffer,const Camera::Camera& camera) {


             LOG_ERROR("getting the buffer");        
                auto* drawCommands = buffer.getBuffer();

                SHADER::IShader* currentShader = nullptr;
                MESH::IMeshGpu* currentMesh = nullptr;

                for(const drawCommand& cd : *drawCommands ){
                    //Shader
                    LOG_ERROR("trying to compare shaders");   
                    if(currentShader != cd.shader){ 
                        currentShader = cd.shader;
                        if(currentShader == nullptr){ LOG_ERROR("shader of the renderable entity is not set, PROGRAM MIGHT CRASH!");
                            continue;
                        }
                        LOG_ERROR("using shader");   
                        currentShader->use();
                        LOG_ERROR("shader usage went well");  
                }
                    currentShader->setMat4("u_model",cd.trans->GetModelMatrix());
                    currentShader->setMat4("u_view",camera.GetViewMatrix());
                    currentShader->setMat4("u_proj",camera.GetProjectionMatrix());
                    // naja eventuell roughness etc aus mateiral noch einbinden aber dafür kein shader datei erstmal

                    if(currentMesh != cd.mesh){
                        currentMesh = cd.mesh;
                        if(currentMesh == nullptr){ LOG_ERROR("mesh of renderable enitty is not set, PROGRAM MIGHT CRASH!");
                            continue;
                        }

                    }
                    currentMesh->draw();
                }
    }
}
