#pragma once
#include <vector>
#include "renderer/Viewport.h"
#include "camera/Camera.h"
#include "window/IWindow.h"

namespace Renderer {

    class ViewportManager {
    public:
        ViewportManager(Window::IWindow* window) : window(window) {}

        void addViewport(std::unique_ptr<Viewport> vp) {
            viewports.push_back(std::move(vp));
        }

        void updateViewports() {
            int width, height;
            window->getSize(width, height);

            for (auto& vp : viewports) {
                vp->setSize(width, height);
                if (vp->getCamera()) {
                    vp->getCamera()->SetAspectRatio(float(width) / height);
                }
            }
        }

        const  std::vector<Viewport*>& getViewports() const {
            std::vector<Viewport*> result;
            for(auto& vp : viewports){
                result.emplace_back(vp.get());
            }
            return result;
         }

    private:
        Window::IWindow* window;
        std::vector<std::unique_ptr<Viewport>> viewports;
    };

} // namespace Renderer