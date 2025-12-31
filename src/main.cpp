#include <algorithm>
#include <iostream>
#include "engine/Input.h"
#include "engine/Renderer.h"
#include "engine/Mesh.h"
#include <GLFW/glfw3.h>
#include <vector>

#include "engine/CameraController.h"
#include "engine/parser.h"
#include "game/Player.h"

int main() {
    // ---------------- Init ----------------
    Engine::InitRenderer(800, 600, "Cube + Floor");
    Engine::InitInput(Engine::GetWindow());
    Engine::WireFrame(false);

    // ---------------- Boden ----------------
    std::vector<float> floorVertices = {
        -10.0f, 0.0f, -10.0f,
         10.0f, 0.0f, -10.0f,
         10.0f, 0.0f,  10.0f,
        -10.0f, 0.0f,  10.0f
    };
    std::vector<uint32_t> floorIndices = {0,1,2, 0,2,3};

    Engine::Entity floor;
    floor.meshID = Engine::LoadMeshIndexed(floorVertices, 3, floorIndices);

    Engine::Shader shader("C:/Users/usman/CLionProjects/fps/assets/shaders/basic.vert",
                          "C:/Users/usman/CLionProjects/fps/assets/shaders/basic.frag");
    floor.material.shader = &shader;
    floor.material.color = Math::Vec3(0.5f, 0.5f, 0.5f); // Grau

    // ---------------- Cubes ----------------
    std::vector<float> cubeVertices = {
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f,0.5f,-0.5f,  -0.5f,0.5f,-0.5f,
        -0.5f,-0.5f,0.5f,   0.5f,-0.5f,0.5f,   0.5f,0.5f,0.5f,   -0.5f,0.5f,0.5f
    };

    std::vector<uint32_t> cubeIndices = {
        4,5,6, 4,6,7,
        0,1,2, 0,2,3,
        0,3,7, 0,7,4,
        1,5,6, 1,6,2,
        3,2,6, 3,6,7,
        0,1,5, 0,5,4
    };
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    std::vector<float> vertices1;
    std::vector<uint32_t> indices1;

    if (!Engine::LoadOBJ("C:/Users/usman/Documents/Anime_charcter.obj", vertices, indices)) {
        std::cerr << "OBJ konnte nicht geladen werden!\n";
    }

    if (!Engine::LoadOBJ("C:/Users/usman/Documents/building.obj", vertices1, indices1)) {
        std::cerr << "OBJ konnte nicht geladen werden!\n";
    }

    Engine::Entity animeGirl;
    animeGirl.meshID = Engine::LoadMeshIndexed(vertices, 3, indices);
    animeGirl.material.shader = &shader;
    animeGirl.material.color = Math::Vec3(0.8f, 0.5f, 0.2f);
    animeGirl.transform.position = Math::Vec3(5.0f, 0.0f, 0.0f);
    animeGirl.transform.scale = Math::Vec3(0.2f, 0.2f, 0.2f);

    Engine::Entity house;
    house.meshID = Engine::LoadMeshIndexed(vertices1, 3, indices1);
    house.material.shader = &shader;

    house.transform.position = Math::Vec3(-4.0f, 0.0f, 0.0f);
    house.transform.scale = Math::Vec3(0.2f, 0.2f, 0.2f);

    Engine::Entity cube1, cube2;
    cube1.meshID = cube2.meshID = Engine::LoadMeshIndexed(cubeVertices, 3, cubeIndices);
    cube1.material.shader = cube2.material.shader = &shader;

    cube1.material.color = Math::Vec3(1.0f, 0.0f, 0.0f); // rot
    cube2.material.color = Math::Vec3(0.0f, 0.0f, 1.0f); // blau
    cube1.transform.scale = Math::Vec3(1.0f, 4.0f, 1.0f);
    cube2.transform.scale = Math::Vec3(1.0f, 4.0f, 1.0f);
    // Cubes auf dem Boden platzieren (Y = 0.5f, da Cube Höhe = 1)
    cube1.transform.position = Math::Vec3(-1.0f, 0.5f, -1.0f);
    cube2.transform.position = Math::Vec3(1.0f, 0.5f, 1.0f);

    // ---------------- Kamera ----------------
    Engine::Camera camera(Math::Vec3(0.0f, 2.0f, 5.0f),
                          Math::Vec3(0.0f, 0.0f, 0.0f),
                          Math::Vec3(0.0f, 1.0f, 0.0f));
    camera.aspect = 800.0f / 600.0f;
    Game::Player player;
    Physics::PhysicsBody body;

    player.Init(Math::Vec3(0.0f, 0.0f, 0.0f), &cube1, &body);
    double lastTime = glfwGetTime();

    ; // Z-Buffer aktivieren

    // ---------------- Main Loop ----------------
    while (Engine::WindowIsOpen()) {
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        if (Engine::IsKeyPressed(GLFW_KEY_ESCAPE))
            Engine::CloseWindow();

        // --- Maus Rotation ---
        player.Update(deltaTime);


        // --- WASD Bewegung ---

        // --- Render ---
        Engine::WindowBackgroundColor(0.1f, 0.23f, 0.3f, 1.0f);
        Engine::ClearScreen();
        Engine::RenderEntity(floor,player.GetCamera());
        Engine::RenderEntity(house, player.GetCamera());

        Engine::RenderEntity(cube1, player.GetCamera());
        Engine::RenderEntity(cube2, player.GetCamera());
        Engine::RenderEntity(animeGirl, player.GetCamera());

        Engine::SwapBuffers();
    }

    Engine::Shutdown();
    return 0;
}
