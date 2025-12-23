#include "engine/Renderer.h"
#include "glad/glad.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "engine/Mesh.h"

namespace Engine {

    GLFWwindow* window = nullptr;
    unsigned int shaderProgram = 0;

    // Callback für Fenstergröße
    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    // Shader-Hilfsfunktion
    unsigned int CompileShader(unsigned int type, const char* source) {
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "Shader Compilation Error:\n" << infoLog << std::endl;
        }
        return shader;
    }

    bool InitRenderer(int width, int height, const std::string& title) {
        if (!glfwInit()) {
            std::cerr << "GLFW init failed\n";
            return false;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD\n";
            return false;
        }

        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        glViewport(0, 0, fbWidth, fbHeight);

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // ---------------- Shader erstellen ----------------
        const char* vertexShaderSource = R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            out  vec4 colorVertex;
            void main() {
                gl_Position = vec4(aPos, 1.0); // direkt Clip-Space
            colorVertex = vec4(0.5, 0.0, 0.0, 1.0);
            }
        )";

        const char* fragmentShaderSource = R"(
            #version 330 core
            out vec4 FragColor;
            in vec4 colorVertex;

            void main() {
                FragColor = colorVertex; // Orange
            }
        )";

        unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
        unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "Shader Program Linking Error:\n" << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return true;
    }

    void ClearScreen() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void SwapBuffers() {
        if (window) {
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void Shutdown() {
        glfwTerminate();
        ShutdownMeshes();
    }

    void RenderMesh(int meshID, float x, float y, float z) {
        const Mesh* mesh = GetMesh(meshID);
        if (!mesh) return;
        glUseProgram(shaderProgram);
        glBindVertexArray(mesh->VAO);

        if(mesh->indexed) {
           glDrawElements(GL_TRIANGLES,mesh->indexCount,GL_UNSIGNED_INT,0);
        }
        else {
            glDrawArrays(GL_TRIANGLES,0,mesh->vertexCount);

        }

        glBindVertexArray(0);
    }

    bool WindowIsOpen() {
        return window && !glfwWindowShouldClose(window);
    }

    GLFWwindow* GetWindowPointer() { return window; }

    void CloseWindow() {
        glfwSetWindowShouldClose(window, true);
    }



    GLFWwindow *GetWindow() {

        return window;
    }
    //_______________________TEST__AND___FUN____METHODS______________________________________
    void WindowBackgroundColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }
    void WireFrame(bool wireframe) {
        if (wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
