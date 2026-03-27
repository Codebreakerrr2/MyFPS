#pragma once
#include "window/IWindow.h"



namespace Renderer {
    class IRenderer {
    public:
        virtual ~IRenderer() = default;
        virtual bool init(Window::IWindow* window) = 0;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;
        virtual void clear(float r, float g, float b, float a) = 0;
        virtual void drawTriangle() = 0;

    };
}
