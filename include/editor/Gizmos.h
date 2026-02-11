#pragma once
#include <iostream>

#include "engine/Entity.h"
#include "engine/Mesh.h"
#include "engine/parser.h"
#include "engine/Shader.h"
#include "math/Vec.h"

class Gizmos {
public:
    Gizmos():
    shader(Engine::Shader(
        "assets/shaders/basic.vert","assets/shaders/basic.frag"))
    {


        // load Mesh
        std::vector<float> verticesSphere;
        std::vector<uint32_t> indicesSphere;
        std::vector<float> vX;
        std::vector<uint32_t> iX;


        if (!Engine::LoadOBJ("assets/meshes/sphere.obj", verticesSphere, indicesSphere)) {
            std::cerr << "OBJ konnte nicht geladen werden!\n";
        }

        // Kugel für Position
        sphereShape.meshID = Engine::LoadMeshIndexed(verticesSphere,3,indicesSphere); // z.B. eine Kugel
        sphereShape.material = Engine::Material(&shader, Math::Vec3(1.0f, 1.0f, 1.0f));

        // X-Achse
        if (!Engine::LoadOBJ("assets/meshes/koordinate.obj", vX, iX)) {
            std::cerr << "OBJ konnte nicht geladen werden!\n";
        }

        XAxisShape.meshID = Engine::LoadMeshIndexed(vX,3,iX); // z.B. Zylinder
        XAxisShape.material = Engine::Material(&shader, Math::Vec3(1.0f, 0.0f, 0.0f));

        // Y-Achse



        YAxisShape.meshID = Engine::LoadMeshIndexed(vX,3,iX);
        YAxisShape.material = Engine::Material(&shader, Math::Vec3(0.0f, 1.0f, 0.0f));

        // Z-Achse



        ZAxisShape.meshID = Engine::LoadMeshIndexed(vX,3,iX);
        ZAxisShape.material = Engine::Material(&shader, Math::Vec3(0.0f, 0.0f, 1.0f));
    }

    ~Gizmos() {}

    void drawGizmos(Engine::Entity& entity);

    void manipulateEntity(Engine::Entity &entity);

private:
    Engine::Shader shader;
    Engine::Entity sphereShape;
    Engine::Entity XAxisShape;
    Engine::Entity YAxisShape;
    Engine::Entity ZAxisShape;
};
