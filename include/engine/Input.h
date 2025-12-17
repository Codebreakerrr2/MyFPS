#pragma once

namespace Engine {

    // Input
    void InitInput();
    bool IsKeyPressed(int keyCode);
    void GetMouseDelta(int& deltaX, int& deltaY);

}
