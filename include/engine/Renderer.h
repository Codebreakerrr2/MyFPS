#pragma once
#include <string>
struct GLFWwindow;


namespace Engine {
    extern GLFWwindow* window;
    bool InitRenderer(int width = 800, int height = 600, const std::string& title = "FPS");

    void ClearScreen();
    void SwapBuffers();

    void RenderMesh(int meshID, float x, float y, float z);
    void Shutdown();

    bool WindowIsOpen();


    void CloseWindow();


    GLFWwindow* GetWindow();


    //_______________________TEST__AND___FUN____METHODS______________________________________
    void WindowBackgroundColor(float r, float g, float b, float a);
    void WireFrame(bool wireframe);
}
