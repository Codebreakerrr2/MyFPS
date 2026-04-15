#pragma once
#include <camera/Camera.h>
#include <mesh/OpenGLMeshPair.h>
#include <renderer/IRenderer.h>
#include <renderer/OpenGLRenderer.h>
#include <window/GLFWWindow.h>

#include "asset_manager/RenderBuffer.h"
#include "renderer/RendererSystem.h"
#include "renderer/ViewportManager.h"


namespace Engine {
    class EngineContext {

    public:
        Asset::Types::RenderBuffer renderBuffer;
        Window::GLFWWindow window;
        Registery rg;
        AssetManager::Manager<SHADER::IShader,ShaderID> shaderManger;
        AssetManager::Manager<MESH::IMeshPair,MeshID> meshManger;
        Camera::Camera mainCamera;
        Renderer::ViewportManager viewportManager;
        Renderer::RendererSystem renderer;
        EngineContext(const std::string& windowName ,int windowWidth, int windowHeight,std::unique_ptr<Renderer::IRenderer> renderer) : window(windowWidth,
            windowHeight, windowName), viewportManager(&window), renderer(std::move(renderer)) {
        }


        void updateRenderBuffer() {
            renderBuffer.updateWriteBuffer(rg);
        }

    };
}
