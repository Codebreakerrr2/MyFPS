#include "engine/Input.h"
#include "engine/Mesh.h"
#include "engine/Renderer.h"

#include <vector>
#include <GLFW/glfw3.h>

int main() {

    Engine::InitRenderer(800, 600, "World Test");
    Engine::InitInput(Engine::GetWindow());

    // ---------------- Mesh einmal laden ----------------
    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    int triangleMeshID = Engine::LoadMesh(vertices, 3);

    // ---------------- Main Loop ----------------
    while (Engine::WindowIsOpen()) {
        if (Engine::IsKeyPressed(GLFW_KEY_ESCAPE))
            Engine::CloseWindow();

        Engine::WindowBackgroundColor(0.10f, 0.23f, 0.3f, 1.0f);
        Engine::ClearScreen();
        Engine::RenderMesh(triangleMeshID, 0.2f, 0.3f, 0.1f);
        Engine::SwapBuffers();
    }


    Engine::Shutdown();

    return 0;
}
