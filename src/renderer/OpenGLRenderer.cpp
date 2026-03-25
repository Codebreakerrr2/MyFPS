#include "OpenGLRenderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Renderer {

bool OpenGLRenderer::init(Window::IWindow* window) {
    this->window = window;
    GLFWwindow* glfwWindow =
        static_cast<GLFWwindow*>(window->getNativeHandle());
    if (!glfwWindow) {
        throw std::runtime_error("Invalid GLFW window handle");
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    int width, height;
    wind                ow->getSize(width, height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    return true;
}
    void GLFWWindow::setFramebufferSizeCallback(GLFWframebuffersizefun cb) {
    glfwSetFramebufferSizeCallback(m_window, cb);
    // kamera anpassen

}


}