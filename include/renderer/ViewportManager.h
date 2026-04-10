#pragma once
#include <vector>
#include "renderer/Viewport.h"
#include "camera/Camera.h"
#include "window/IWindow.h"

namespace Renderer {

    class ViewportManager {
    public:
        ViewportManager(Window::IWindow* window) : window(window) {}

        void addViewport(Viewport& vp) {
            viewports.push_back(&vp);
        }

        void updateViewports() {
            int width, height;
            window->getSize(width, height);

            for (auto* vp : viewports) {
                vp->setSize(width, height);
                if (vp->getCamera()) {
                    vp->getCamera()->SetAspectRatio(float(width) / height);
                }
            }
        }

        const std::vector<Viewport*>& getViewports() const { return viewports; }

    private:
        Window::IWindow* window;
        std::vector<Viewport*> viewports;
    };

} // namespace Renderer