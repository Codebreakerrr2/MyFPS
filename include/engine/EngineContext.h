#pragma once
#include <camera/Camera.h>
#include <mesh/OpenGLMeshPair.h>
#include <renderer/IRenderer.h>
#include <renderer/OpenGLRenderer.h>
#include <window/GLFWWindow.h>

#include "asset_manager/RenderBuffer.h"


namespace Engine {
    class EngineContext {

    public:
        Asset::Types::RenderBuffer renderBuffer;
        Window::GLFWWindow window;
        Registery rg;
        AssetManager::Manager<SHADER::IShader,ShaderID> shaderManger;
        AssetManager::Manager<MESH::IMeshPair,MeshID> meshManger;
        Camera::Camera mainCamera;
        Renderer::OpenGLRenderer renderer;
        EngineContext():window(800,600,"FPS"){}


        void updateRenderBuffer() {
            renderBuffer.updateRegistryBuffer(rg);
        }

    };
}
