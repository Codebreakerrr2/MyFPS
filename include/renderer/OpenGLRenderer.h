#pragma once
#include "IRenderer.h"
#include <vector>
namespace Renderer{
class OpenGLRenderer : public IRenderer{
	public:

         bool init(Window::IWindow* window) override;
         void beginFrame() override{};// braucht man nicht opengl
         void endFrame() override{};// braucht man nicht opengl
         void clear(float r, float g, float b, float a) override;
         void drawTriangle(const Engine::Registery& rg,const Camera::Camera& camera) override;
         void filterRenderables(const Engine::Registery& rg) override;
         void addViewport(Viewport viewport)override;
         void renderViewports(const Engine::Registery& rg) override;
	private:
		Window::IWindow* window;
                std::vector<Viewport> viewports;
                std::vector<drawCommand> renderables;
                bool renderablesDirty = true;

};
}
