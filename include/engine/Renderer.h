#pragma once
#include <string>

#include "Camera.h"
#include "Entity.h"
struct GLFWwindow;


namespace Engine {
    class IShader;


    enum class RenderType {
        OPENGL, VULKAN, DIRECTX
    };
    static RenderType renderType = RenderType::OPENGL;
    inline RenderType GetRenderType() {
        return renderType;
    }
    inline void SetRenderType(RenderType type) {
        renderType = type;
    }


    extern GLFWwindow* window;
    bool InitRenderer(int width = 800, int height = 600, const std::string& title = "FPS");

    void ClearScreen();
    void SwapBuffers();

    void RenderMesh(int meshID, float x, float y, float z);
    void RenderEntity(const Entity& entity, const Camera& camera);
    void RenderEditorOverlay(const Entity& entity, const Camera& camera,IShader& shader);
    void Shutdown();

    bool WindowIsOpen();


    void CloseWindow();


    GLFWwindow* GetWindow();
    void GetWindowSize(int& width, int& height);



    //_______________________TEST__AND___FUN____METHODS______________________________________
    void WindowBackgroundColor(float r, float g, float b, float a);
    void WireFrame(bool wireframe);
}
