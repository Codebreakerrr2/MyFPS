#include "renderer/OpenGLRenderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <window/GLFWWindow.h>

#include "window/IWindow.h"

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
    window->getSize(width, height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    return true;
}
    void OpenGLRenderer::clear(float r, float g, float b, float a)  {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



    void OpenGLRenderer::drawTriangle() {


    }
}
