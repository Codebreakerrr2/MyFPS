#pragma once
#include <unordered_map>

#include "IInput.h"

namespace Input {

    class InputXBOX : public IInput {
    public:
        InputXBOX(int joystickID = 0);

        bool IsActionPressed(Action action) const override;
        float GetAxis(Action action) const override;

        void SetJoystickID(int jid) { joystickID = jid; }

    private:
        int joystickID; // GLFW joystick index (0–15)

        // Mapping Action → Button/Axis Index
        std::unordered_map<Action, int> buttonMap;
        std::unordered_map<Action, int> axisMap;
    };

} // namespace Input