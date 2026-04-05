
#include "input/InputKeyboard.h"

#include <GLFW/glfw3.h> // GLFW für Tastaturabfrage

namespace Input {

    // Konstruktor: Mapping Action → Taste
    InputKeyboard::InputKeyboard() {
        keyMap[Action::Forward]  = GLFW_KEY_W;
        keyMap[Action::Backward] = GLFW_KEY_S;
        keyMap[Action::Left]     = GLFW_KEY_A;
        keyMap[Action::Right]    = GLFW_KEY_D;
        keyMap[Action::Jump]     = GLFW_KEY_SPACE;
        keyMap[Action::Shoot]    = GLFW_KEY_LEFT_CONTROL;
        keyMap[Action::LookUp]   = GLFW_KEY_UP;
        keyMap[Action::LookDown] = GLFW_KEY_DOWN;
        keyMap[Action::LookLeft] = GLFW_KEY_LEFT;
        keyMap[Action::LookRight]= GLFW_KEY_RIGHT;
        keyMap[Action::Close]= GLFW_KEY_ESCAPE;
    }

    // Prüfen, ob Aktion gedrückt ist
    bool InputKeyboard::IsActionPressed(Action action) const {
        auto it = keyMap.find(action);
        if (it == keyMap.end()) return false;

        int key = it->second;

        // GLFW-Kontext muss existieren
        return glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS;
    }

    // Achsenwerte für Bewegung (Forward/Backward, Left/Right)
    float InputKeyboard::GetAxis(Action action) const {
        switch (action) {
            case Action::Forward:
            case Action::Backward:
                return (IsActionPressed(Action::Forward)  ? 1.0f : 0.0f)
                     + (IsActionPressed(Action::Backward) ? -1.0f : 0.0f);

            case Action::Right:
            case Action::Left:
                return (IsActionPressed(Action::Right) ? 1.0f : 0.0f)
                     + (IsActionPressed(Action::Left)  ? -1.0f : 0.0f);

            default:
                return 0.0f;
        }
    }

} // namespace Input