#pragma once
#include <unordered_map>

namespace Input {

    enum class Action {
        Forward,
        Backward,
        Left,
        Right,
        Jump,
        Shoot,
        LookUp,
        LookDown,
        LookLeft,
        LookRight,
        Close
    };

    class IInput {
    public:
        virtual ~IInput() = default;
        virtual bool IsActionPressed(Action action) const = 0;
        virtual float GetAxis(Action action) const = 0;

    };

}
