
#include "engine/Input.h"
#include "engine/Renderer.h"

#include "world/Map.h"

int main() {

    Engine::InitRenderer(800, 600, "World Test");
    Engine::InitInput(Engine::GetWindow());
    while(Engine::WindowIsOpen()) {
        if (Engine::IsKeyPressed(GLFW_KEY_ESCAPE)) Engine::CloseWindow();
        // einfacher Frame-Loop
        Engine::ClearScreen();
        Engine::WindowBackgroundColor(0.10f, 0.23f, 0.3f, 1.0f);
        Engine::SwapBuffers();
    }
    Engine::Shutdown();
    return 0;
}
