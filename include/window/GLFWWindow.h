#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include "window/IWindow.h"

namespace Window {
    class GLFWWindow : public IWindow {
	public:
        GLFWWindow( int width, int height,const std::string& title);
        // bool isOpen() const override;
         void close()  override;
         void getSize(int& width, int& height) const override;
         void pollEvents() override;
		 void setFramebufferSizeCallback(GLFWframebuffersizefun cb);
         void swapBuffers() override;
         void setBackgroundColor(float r, float g, float b, float a) override;

        void *getNativeHandle() override;

    private:
        GLFWwindow* window;
    };
}