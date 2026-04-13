#pragma once


#include "asset_manager/Types.h"
#include "window/IWindow.h"
#include "renderer/Viewport.h"
namespace Asset::Types{
    class RenderBuffer;
}
namespace Camera{
    class Camera;
}
namespace Engine{
    class Registery;
}

namespace Renderer {



    class IRenderer {
    public:
        virtual ~IRenderer() = default;
        virtual bool init(Window::IWindow* window) = 0;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;
        virtual void clear(float r, float g, float b, float a) = 0;
        virtual void drawTriangle(Asset::Types::RenderBuffer& buffer,const Camera::Camera& camera) = 0;
        virtual void addViewport(Viewport& viewport) = 0;
        virtual void renderViewports(Asset::Types::RenderBuffer& buffer) =0;
        virtual void setViewPort(Viewport& viewport) = 0;
        virtual void setScissor(Viewport& viewport) = 0;
        virtual void enableScissor() = 0;
        virtual void disableScissor() =0;
    };
}
