#pragma once
#include <unordered_map>

#include "IInput.h"

namespace Input {

    class InputKeyboard : public IInput {
    public:
        InputKeyboard();

        bool IsActionPressed(Action action) const override;
        float GetAxis(Action action) const override;

    private:
        // Mapping Action → Taste (z.B. GLFW KeyCodes)
        std::unordered_map<Action, int> keyMap;
    };

} // namespace Input