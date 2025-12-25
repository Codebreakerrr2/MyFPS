#include "engine/Renderer.h"
#include "engine/Entity.h"
#include "glad/glad.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "engine/Mesh.h"

namespace Engine {

    GLFWwindow* window = nullptr;

    // Callback für Fenstergröße
    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
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
        glEnable(GL_DEPTH_TEST);

        return true;
    }

    void ClearScreen() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    /* this function is just for Testing and Learning purposes no Use at All
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
    }*/

    void RenderEntity(const Entity& entity,const Camera& camera) {
        const Mesh* mesh = GetMesh(entity.meshID);
        if (!mesh || !entity.material.shader) {
            std::cerr << "Mesh shader not found\n";
            return;
        }

        Shader& shader = *entity.material.shader;

        shader.use();
        shader.setVec3("color", entity.material.color);
        shader.setMat4("u_model",entity.transform.GetModelMatrix());
        shader.setMat4("u_view",camera.GetViewMatrix());
        shader.setMat4("u_proj",camera.GetProjectionMatrix());
        glBindVertexArray(mesh->VAO);

        if (mesh->indexed)
            glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, mesh->vertexCount);



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
