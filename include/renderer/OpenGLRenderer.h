#pragma once
#include "IRenderer.h"

namespace Renderer{
class OpenGLRenderer : public IRenderer{
	public:
        ~OpenGLRenderer() override;
         bool init(Window::IWindow* window) override;
         void beginFrame() override;
         void endFrame() override;
         void clear(float r, float g, float b, float a) override;
         void drawTriangle() override;

	private:
		Window::IWindow* window;
};
}