#include "input/InputMouse.h"
#include "GLFW/glfw3.h"

namespace Input {

    InputMouse::InputMouse() {
        mouseMap[Action::Shoot] = GLFW_MOUSE_BUTTON_LEFT;
    }

    void InputMouse::Update() {
        double xpos, ypos;
        glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);

        deltaX = static_cast<float>(xpos - lastX);
        deltaY = static_cast<float>(lastY - ypos);

        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
    }

    bool InputMouse::IsActionPressed(Action action) const {
        auto it = mouseMap.find(action);
        if (it != mouseMap.end()) {
            int button = it->second;
            return glfwGetMouseButton(glfwGetCurrentContext(), button) == GLFW_PRESS;
        }
        return false;
    }

    float InputMouse::GetAxis(Action) const {
        return 0.0f; // Maus hat keine klassischen Achsen hier
    }

    float InputMouse::GetMouseDeltaX() const {
        return deltaX;
    }

    float InputMouse::GetMouseDeltaY() const {
        return deltaY;
    }

}