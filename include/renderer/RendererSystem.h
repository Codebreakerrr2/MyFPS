#pragma once
#include <vector>
#include <memory>

#include "IRenderer.h"
#include "Viewport.h"
#include "profiling/LoggerManager.h"

namespace Renderer {
    class Viewport;


    class RendererSystem {

    private:
        std::vector<Renderer::Viewport*> viewports;
        std::unique_ptr<Renderer::IRenderer> renderer;

    public:
        RendererSystem(std::unique_ptr<Renderer::IRenderer> renderer)
            : renderer(std::move(renderer)) {}

        void addViewport(Renderer::Viewport& viewport) {
            viewports.push_back(&viewport);
            LOG_SUCCESS("Viewport " + viewport.getName() + " added to viewport collection!");
        }

        void addViewport(std::vector<Renderer::Viewport*> vps) {
            for (auto* vp :vps) {
                viewports.push_back(vp);
                LOG_SUCCESS("Viewport " + viewport.getName() + " added to viewport collection!");
            }
        }

        void renderViewports(Asset::Types::RenderBuffer& buffer) {

            for (auto* vp : viewports) {

                renderer->enableScissor();
                renderer->setViewPort(*vp);
                renderer->setScissor(*vp);

                renderer->drawTriangle(buffer, *vp->getCamera());
            }

            renderer->disableScissor();
        }
    };
}