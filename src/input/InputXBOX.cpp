#include "input/InputXBOX.h"
#include <GLFW/glfw3.h>

namespace Input {

InputXBOX::InputXBOX(int jid) : joystickID(jid) {
    // Button Mapping (Xbox unter Windows / GLFW)
    buttonMap[Action::Jump]     = 0; // A
    buttonMap[Action::Shoot]    = 5; // RT oder RB, je nach Mapping
    buttonMap[Action::LookUp]   = -1; // Maus/Stick benutzt Achse
    buttonMap[Action::LookDown] = -1;
    buttonMap[Action::LookLeft] = -1;
    buttonMap[Action::LookRight]= -1;

    // Axis Mapping (Linker Stick)
    axisMap[Action::Forward]  = 1; // Y-Achse links Stick, -1 für Vorwärts
    axisMap[Action::Backward] = 1; // gleiche Achse, invertiert
    axisMap[Action::Left]     = 0; // X-Achse links Stick
    axisMap[Action::Right]    = 0; // X-Achse links Stick
    axisMap[Action::LookRight] = 2; // Right Stick X
    axisMap[Action::LookLeft]  = 2;
    axisMap[Action::LookUp]    = 3; // Right Stick Y
    axisMap[Action::LookDown]  = 3;
}

// Prüfen, ob Button gedrückt ist
bool InputXBOX::IsActionPressed(Action action) const {
    if (buttonMap.find(action) == buttonMap.end()) return false;

    int button = buttonMap.at(action);
    if (button < 0) return false; // keine Taste zugeordnet

    int count;
    const unsigned char* buttons = glfwGetJoystickButtons(joystickID, &count);
    if (!buttons || button >= count) return false;

    return buttons[button] == GLFW_PRESS;
}

// Achsenwerte für Bewegung
float InputXBOX::GetAxis(Action action) const {
    int axisIndex = -1;
    if (axisMap.find(action) != axisMap.end())
        axisIndex = axisMap.at(action);

    if (axisIndex < 0) return 0.0f;

    int count;
    const float* axes = glfwGetJoystickAxes(joystickID, &count);
    if (!axes || axisIndex >= count) return 0.0f;

    float value = axes[axisIndex];

    // Achsen normalisieren für Forward/Backward invertiert (Y-Achse nach vorne -1)
    switch (action) {
        case Action::Forward:  return -value > 0 ? -value : 0.0f;
        case Action::Backward: return -value < 0 ? -value : 0.0f;
        case Action::Right:    return value > 0 ? value : 0.0f;
        case Action::Left:     return value < 0 ? -value : 0.0f;
        case Action::LookRight: return value > 0 ? value : 0.0f;
        case Action::LookLeft:  return value < 0 ? -value : 0.0f;
        case Action::LookUp:    return value < 0 ? -value : 0.0f; // invert Y
        case Action::LookDown:  return value > 0 ? value : 0.0f;
        default: return 0.0f;
    }
}

} // namespace Input