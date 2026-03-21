#pragma once
#include "IWindow.h"
#include <GLFW/glfw3.h>
#include <iostream>

class GLFWWindow : public IWindow {
private:
    GLFWwindow* window = nullptr;
    float bgColor[4] = {0.f, 0.f, 0.f, 1.f};

public:
    // Konstruktor: Fenster erstellen
    GLFWWindow(int width, int height, const char* title) {
        if (!glfwInit()) {
            std::cerr << "GLFW init failed\n";
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        // Viewport initial setzen
        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        glViewport(0, 0, fbWidth, fbHeight);

        // Resize Callback registrieren
        glfwSetFramebufferSizeCallback(window,[](GLFWwindow* win, int w, int h) {
            glViewport(0, 0, w, h);
            //TODO camera change
        });
    }

    ~GLFWWindow() override {
        if (window) glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool isOpen() const override {
        return window && !glfwWindowShouldClose(window);
    }

    void close() override {
        if (window) glfwSetWindowShouldClose(window, true);
    }

    void getSize(int& width, int& height) const override {
        if (window) glfwGetFramebufferSize(window, &width, &height);
    }

    void pollEvents() override {
        glfwPollEvents(); // Holt alle Events: Resize, Input, Close
    }

    void swapBuffers() override {
        if (window) glfwSwapBuffers(window);
    }

    void setBackgroundColor(float r, float g, float b, float a) override {
        bgColor[0] = r; bgColor[1] = g; bgColor[2] = b; bgColor[3] = a;
        glClearColor(r, g, b, a);
    }

    // Optional: direkter Zugriff auf GLFWwindow*
    GLFWwindow* getGLFWwindow() const { return window; }
};