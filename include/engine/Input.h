#pragma once
#include "GLFW/glfw3.h"


namespace Input {



    class Input{
        public:
        virtual ~Input() = default;



    }


    // Input altes system
    void InitInput(GLFWwindow* window);
    bool IsKeyPressed(int keyCode);
    bool IsMouseButtonPressed(int keyCode);
    void GetMouseDelta(int& deltaX, int& deltaY);
    void setMouseSensitivity(float sensitivity);
    float getMouseSensitivity();
    void getMousePosition(GLFWwindow* window,double& mouseX, double& mouseY);

}
