#pragma once
#include <vector>
#include <memory>

namespace Renderer {
    class Viewport;
}

class RendererSystem {

private:
    std::vector<Viewport*> viewports;
    std::unique_ptr<IRenderer> renderer;

public:
    RendererSystem(std::unique_ptr<IRenderer> renderer)
        : renderer(std::move(renderer)) {}

    void addViewport(Viewport& viewport) {
        viewports.push_back(&viewport);
        LOG_SUCCESS("Viewport " + viewport.getName() + " added to viewport collection!");
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