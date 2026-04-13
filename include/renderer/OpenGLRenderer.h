#pragma once
#include "IRenderer.h"
#include <vector>
#include "asset_manager/Types.h"

namespace Renderer{
class OpenGLRenderer : public IRenderer{
	public:

         bool init(Window::IWindow* window) override;
         void beginFrame() override{};// braucht man nicht opengl
         void endFrame() override{};// braucht man nicht opengl
         void clear(float r, float g, float b, float a) override;
         void drawTriangle(Asset::Types::RenderBuffer& buffer,const Camera::Camera& camera) override;
         void setViewPort(Viewport& viewport) override;
         void setScissor(Viewport& viewport) override;
         void enableScissor() override;
         void disableScissor() override;
         
	private:
		Window::IWindow* window;
           

};
}
