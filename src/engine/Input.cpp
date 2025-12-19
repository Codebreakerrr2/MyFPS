#include "engine/Input.h"
#include <windows.h>
#include "engine/Renderer.h"

namespace Engine {


    static double lastMouseX = 0, lastMouseY = 0;
    static bool firstMouse = true;

    void InitInput(GLFWwindow* win) {
        window = win;
        // Optional: Cursor sperren
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    bool IsKeyPressed(int keyCode) {
        return glfwGetKey(window, keyCode) == GLFW_PRESS;
    }

    void GetMouseDelta(int& deltaX, int& deltaY) {
        double mouseX, mouseY;
        glfwGetCursorPos(window,&mouseX,&mouseY);

        if (firstMouse) {
            mouseX = lastMouseX;
            mouseY = lastMouseY;
            firstMouse = false;
        }
        deltaX = static_cast<int>(mouseX - lastMouseX);
        deltaY = static_cast<int>(mouseY - lastMouseY);
        lastMouseX = mouseX;
        lastMouseY = mouseY;
    }


}
