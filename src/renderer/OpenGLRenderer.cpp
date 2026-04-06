#include "renderer/OpenGLRenderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <window/GLFWWindow.h>
#include "asset_manager/Registery.h"
#include "camera/Camera.h"
#include "mesh/IMeshPair.h"
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
    LOG_SUCCESS(OpenGLRenderer initialized!);
    return true;
}
    void OpenGLRenderer::clear(float r, float g, float b, float a)  {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



     void OpenGLRenderer::addViewport(Viewport viewport){
        viewports.emplace_back(viewport);
        LOG_SUCCESS("Viewport "+ viewport.getName()+" added to viewport collection!");
    }

    void OpenGLRenderer::renderViewports(const Engine::Registery& rg){
        glEnable(GL_SCISSOR_TEST);
        for(auto& vp: viewports){
            glViewport(vp.getX(),vp.getY(),vp.getWidth(),vp.getHeight());
            glScissor(vp.getX(), vp.getY(), vp.getWidth(), vp.getHeight());
            LOG_INFO("viewport "+vp.getName()+" starting to draw!")
            drawTriangle(rg,vp.getCamera();)
            LOG_INFO("viewport "+ vp.getName()," finished drawing!")
        }
       glDisable(GL_SCISSOR_TEST);

    }


    void OpenGLRenderer::filterRenderables(const Engine::Registery& rg){
            const Asset::Pool<MeshComponent>& meshPool = rg.getPool<MeshComponent>();
        const Asset::Pool<TransformComponent>& transformPool = rg.getPool<TransformComponent>();
        const Asset::Pool<MaterialComponent>& materialPool = rg.getPool<MaterialComponent>();
        std::vector<drawCommand> list;
        for(const auto& e : meshPool.getEntities()){
            if(rg.has<TransformComponent>(e) && rg.has<MaterialComponent>(e)){
                list.emplace_back(
                    drawCommand{
                        materialPool.getComponent(e)->shader(),
                        materialPool.getComponent(e),
                        meshPool.getComponent(e)->meshtupel()->getGpuMesh(),
                        transformPool.getComponent(e)
                    }
                );
            }
        }
          auto compare = [](drawCommand& a, drawCommand& b){
            if(a.shader != b.shader) return a.shader<b.shader;
            if(a.mat->mateirals != b.mat->mateirals) return a.mat->mateirals < b.mat->mateirals;
            return a.mesh < b.mesh;
        };
        std::sort(list.begin(),list.end(), compare);
        renderables = std::move(list);
        LOG_INFO("renderables has been updated!");
    }

    void OpenGLRenderer::drawTriangle(const Engine::Registery& rg,const Camera::Camera& camera) {
  
                if(renderablesDirty){
                    filterRenderables(rg);
                    renderablesDirty = false;
                }

                SHADER::IShader* currentShader = nullptr;
                MESH::IMeshGpu* currentMesh = nullptr;

                for(const drawCommand& cd : renderables ){
                    //Shader
                    if(currentShader != cd.shader){ 
                        currentShader = cd.shader;
                        if(currentShader == nullptr){ LOG_ERROR("shader of the renderable entity is not set, PROGRAM CRASH!");
                            continue;
                        }
                        currentShader->use();
                }
                    currentShader->setMat4("u_model",cd.trans->GetModelMatrix());
                    currentShader->setMat4("u_view",camera.GetViewMatrix());
                    currentShader->setMat4("u_proj",camera.GetProjectionMatrix());
                    // naja eventuell roughness etc aus mateiral noch einbinden aber dafür kein shader datei erstmal

                    if(currentMesh != cd.mesh){
                        currentMesh = cd.mesh;
                        if(currentMesh == nullptr){ LOG_ERROR("mesh of renderable enitty is not set, PROGRAM CRASH!");
                            continue;
                        }

                    }
                    currentMesh->draw();
                }
    }
}
