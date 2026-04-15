#pragma once
#include "asset_manager/RenderBuffer.h"
#include "renderer/RendererSystem.h"
#include "renderer/ViewportManager.h"
#include "window/GLFWWindow.h"


class RendererContext {

    AssetManager::Manager<SHADER::IShader, Asset::Types::ShaderID> shaderManger;
    AssetManager::Manager<MESH::IMeshPair, Asset::Types::MeshID> meshManger;
    Asset::Types::RenderBuffer renderBuffer;
    Window::GLFWWindow window;
    Renderer::ViewportManager viewportManager;
    Renderer::RendererSystem renderer;
};
