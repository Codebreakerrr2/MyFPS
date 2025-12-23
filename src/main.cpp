#include <iostream>

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
        -0.5f, -0.5f, 0.9f,//
         0.5f, -0.5f, 0.9f,//
         0.5f,  0.5f, 0.9f,
        -0.5f, 0.5f, 0.9f
    };
    const std::vector<uint32_t> indices = {
        0,1,2,
        0,2,3
    };

    int mesh_id = Engine::LoadMeshIndexed(vertices, 3,indices);

    // ---------------- Main Loop ----------------
    while (Engine::WindowIsOpen()) {
        if (Engine::IsKeyPressed(GLFW_KEY_ESCAPE))
            Engine::CloseWindow();
        Engine::WindowBackgroundColor(0.10f, 0.23f, 0.3f, 1.0f);
        Engine::ClearScreen();
        Engine::RenderMesh(mesh_id, 0.2f, 0.9f, 0.9f);
        Engine::SwapBuffers();

    }
    int nrAttributes;


    Engine::Shutdown();

    return 0;
}
