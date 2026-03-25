#pragma once
#include "IWindow.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

GLFWWindow::GLFWWindow(int width, int height, const char* title){
	if(!glfwInit()){
		throw std::runtime_error("Failed to initialize GLFW")
	}
	// Optional: OpenGL Version festlegen
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
glfwMakeContextCurrent(window);
glfwSetFramebufferSizeCallback(m_window, cb);
}

void GLFWWindow::close() {
    glfwSetWindowShouldClose(m_window, true);
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
    glClear(GL_COLOR_BUFFER_BIT);


void* GLFWWindow::getNativeHandle() {
	return window;
}