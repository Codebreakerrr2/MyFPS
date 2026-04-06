#include "window/GLFWWindow.h"
#include <iostream>

#include "profiling/LoggerManager.h"

namespace Window {

    GLFWWindow::GLFWWindow(int width, int height, const std::string& title) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        // OpenGL Version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);
        LOG_SUCCESS("GLFWWindow initialized and sat as current window");
        lastTime = static_cast<float>(glfwGetTime());
    }

    GLFWWindow::~GLFWWindow() {
        if (window) glfwDestroyWindow(window);
        glfwTerminate();
        LOG_WARNING("GLFWWinodw has been destroyed and glfw has been terminated");
    }

    bool GLFWWindow::isOpen() const {
        return !glfwWindowShouldClose(window);
    }

    void GLFWWindow::close() {
        glfwSetWindowShouldClose(window, true);
        LOG_INFO("GLFWWindow is sat to close");
    }

    void GLFWWindow::getSize(int& width, int& height) const {
        glfwGetWindowSize(window, &width, &height);
    }

    void GLFWWindow::pollEvents() {
        glfwPollEvents();
    }

    void GLFWWindow::swapBuffers() {
        glfwSwapBuffers(window);
    }

    void GLFWWindow::setBackgroundColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLFWWindow::setFramebufferSizeCallback(GLFWframebuffersizefun cb) {
        glfwSetFramebufferSizeCallback(window, cb);
        LOG_SUCCESS("frameBufferSize call back function has been registered!");
    }

    void* GLFWWindow::getNativeHandle() {
        return window;
    }

    // 🔹 DeltaTime pro Frame
    float GLFWWindow::getDeltaTime() {
        float currentTime = static_cast<float>(glfwGetTime());
        float delta = currentTime - lastTime;
        lastTime = currentTime;
        return delta;
    }

} // namespace Window