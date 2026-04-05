#pragma once
#include "IInput.h"
#include <unordered_map>

namespace Input {

    class InputMouse : public IInput {
    public:
        InputMouse();

        void Update();

        bool IsActionPressed(Action action) const override;
        float GetAxis(Action action) const override;

        float GetMouseDeltaX() const ;
        float GetMouseDeltaY() const ;

    private:
        std::unordered_map<Action, int> mouseMap;

        float lastX = 0.0f, lastY = 0.0f;
        float deltaX = 0.0f, deltaY = 0.0f;
    };

}