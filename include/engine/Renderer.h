#pragma once
#include <string>

namespace Engine{

    bool initRenderer(int width = 800, int height = 600, const std::string& title = "FPS");
    void ClearScreen();
    void SwapBuffers();
    void RenderTexture(const std::string& path, int x, int y);
    void RenderMesch(int meshID, float x, float y, float z);
    




}