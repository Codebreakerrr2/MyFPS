#pragma once
#include "asset_manager/RenderBuffer.h"
#include "renderer/RendererSystem.h"
#include "renderer/ViewportManager.h"
#include "window/GLFWWindow.h"

namespace Context {
    class RendererContext {


    public:
        Window::GLFWWindow window;
        Renderer::ViewportManager viewportManager;
        Renderer::RendererSystem rendererSystem;
        RendererContext(int windowWidth,
            int windowHeight,
            const std::string& windowName,
            std::unique_ptr<Renderer::IRenderer> renderer
            ): window(windowWidth, windowHeight, windowName), viewportManager(&window),rendererSystem(std::move(renderer)) {
            rendererSystem.getNativeRenderer()->init(&window); //Renderer muss window kennen
        }

        friend class FrameContext;
    };
}