#pragma once
#include "IRenderer.h"
#include <vector>
namespace Renderer{
class OpenGLRenderer : public IRenderer{
	public:
        ~OpenGLRenderer() override;
         bool init(Window::IWindow* window) override;
         void beginFrame() override;
         void endFrame() override;
         void clear(float r, float g, float b, float a) override;
         void drawTriangle(const Engine::Registery& rg,const Camera& camera) override;
         void filterRenderables(const Engine::Registery& rg) override;

	private:
		Window::IWindow* window;
                std::vector<drawCommand> renderables;
                bool renderablesDirty = false;
};
}
