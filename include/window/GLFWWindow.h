#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include "window/IWindow.h"


namespace Window {

    class GLFWWindow : public IWindow {
    public:
        GLFWWindow(int width, int height, const std::string& title);
        ~GLFWWindow();

        // IWindow Interface
        bool isOpen() const override;
        void close() override;
        void getSize(int& width, int& height) const override;
        void pollEvents() override;
        void swapBuffers() override;
        void setBackgroundColor(float r, float g, float b, float a) override;
        void setFramebufferSizeCallback(GLFWframebuffersizefun cb) ;
        void* getNativeHandle() override;

        // 🔹 DeltaTime pro Frame
        float getDeltaTime();

    private:
        GLFWwindow* window = nullptr;
        float lastTime = 0.0f;
    };

} // namespace Window