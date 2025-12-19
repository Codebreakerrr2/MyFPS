#pragma once
#include "GLFW/glfw3.h"


namespace Engine {

    // Input
    void InitInput(GLFWwindow* window);
    bool IsKeyPressed(int keyCode);
    void GetMouseDelta(int& deltaX, int& deltaY);

}
