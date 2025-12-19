#include "engine/Renderer.h"
#include "glad/glad.h"
#include <iostream>
#include "GLFW/glfw3.h"

namespace Engine {




    GLFWwindow* window = nullptr;

    //CAll Back Function for Window Resizing!
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }


    bool InitRenderer(int width, int height, const std::string& title) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
       // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); uncomment for Mac
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            std::cout << "Failed to create GLFW window." << std::endl;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        int fbHeight, fbWidth;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        glViewport(0,0,fbWidth,fbHeight);

        glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
        return true;
    }

    void ClearScreen() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void SwapBuffers() {
        if (window) {
            // Backbuffer ↔ Frontbuffer
            glfwSwapBuffers(window);

            // Input/Event-Handling, damit Fenster reagiert
            glfwPollEvents();
        }
    }


    void Shutdown() {

    }


    void RenderMesh(int meshID, float x, float y, float z) {


    }
    bool WindowIsOpen() {
        if (window) {
            return !glfwWindowShouldClose(window);
        }
        std::cout << "Window have not been created!" << std::endl;
        return true;
    }
    GLFWwindow* GetWindowPointer() {
        return window;
    }
    void CloseWindow() {
        glfwSetWindowShouldClose(window, true);
    }
    GLFWwindow* GetWindow() {
        return window;
    }

    //TEST METHODE
    void WindowBackgroundColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

}
