#include <gtest/gtest.h>

#include "engine/Entity.h"
#include "engine/Mesh.h"
#include "math/Vec.h"

TEST(Vec3Test, NormalizeX) {
    Math::Vec3 v(3.0f, 0.0f, 0.0f);
    Math::Vec3 n = Math::Normalize(v);

    EXPECT_NEAR(n.x, 1.0f, 0.0001f);
    EXPECT_NEAR(n.y, 0.0f, 0.0001f);
    EXPECT_NEAR(n.z, 0.0f, 0.0001f);
}


#include "geometry/Geometry.h"
#include "engine/Camera.h"


// Dummy Kamera für Tests
Engine::Camera createTestCamera() {
    Engine::Camera cam;
    cam.position = Math::Vec3(1.0f, 2.0f, 3.0f);
    cam.front = Math::Vec3(0.0f, 0.0f, -1.0f);
    cam.up = Math::Vec3(0.0f, 1.0f, 0.0f);
    return cam;
}

// -----------------------------
// Tests für GetMouseRay
// -----------------------------
TEST(GeometryTest, GetMouseRay_OriginMatchesCameraPosition) {
    Engine::Camera cam = createTestCamera();
    Geometry::Ray ray = Geometry::GetMouseRay(&cam);

    EXPECT_FLOAT_EQ(ray.origin.x, cam.position.x);
    EXPECT_FLOAT_EQ(ray.origin.y, cam.position.y);
    EXPECT_FLOAT_EQ(ray.origin.z, cam.position.z);
}

TEST(Geometry, GetMouseRay_DirectionIsNormalized) {
    Engine::Camera cam = createTestCamera();
    Geometry::Ray ray = Geometry::GetMouseRay(&cam,Math::Vec2(50,50));

    float length = std::sqrt(ray.direction.x * ray.direction.x +
                             ray.direction.y * ray.direction.y +
                             ray.direction.z * ray.direction.z);

    EXPECT_NEAR(length, 1.0f, 1e-5);
}

TEST(Geometry, GetMouseRay_DirectionPointsForward) {
    Engine::Camera cam = createTestCamera();
    Geometry::Ray ray = Geometry::GetMouseRay(&cam,Math::Vec2(50,50));

    // Da Front = (0,0,-1), Ray sollte in etwa gleiche Richtung haben
    float dot = ray.direction.x * cam.front.x +
                ray.direction.y * cam.front.y +
                ray.direction.z * cam.front.z;

    EXPECT_GT(dot, 0.9f); // fast parallel
}
TEST(AABB,GetBoudingBox) {
    // if verticies !=  x*3, x from uint
    std::vector<float> vertices = {1,2};
    Geometry::AABB ab= Engine::GetBoundingBox(vertices);


    EXPECT_FLOAT_EQ(ab.max.x, 0.0f);
    EXPECT_FLOAT_EQ(ab.max.y, 0.0f);
    EXPECT_FLOAT_EQ(ab.max.z, 0.0f);
    EXPECT_FLOAT_EQ(ab.min.x, 0.0f);
    EXPECT_FLOAT_EQ(ab.min.y, 0.0f);
    EXPECT_FLOAT_EQ(ab.min.z, 0.0f);

    //if verticies ok
    std::vector<float> vertices2 = {1.0f,2.0f,3.0f,4.0f,5.0f,-6.0f};
    Geometry::AABB ab2= Engine::GetBoundingBox(vertices2);

    EXPECT_FLOAT_EQ(ab2.max.x, 4.0f);
    EXPECT_FLOAT_EQ(ab2.max.y, 5.0f);
    EXPECT_FLOAT_EQ(ab2.max.z, 3.0f);
    EXPECT_FLOAT_EQ(ab2.min.x, 1.0f);
    EXPECT_FLOAT_EQ(ab2.min.y, 2.0f);
    EXPECT_FLOAT_EQ(ab2.min.z, -6.0f);

}
TEST(EntityBoudingBox,GetBoudingBox) {

// Exception because iam assume the MeshLoader functions correct!
    // ---------------- Cubes ----------------
    std::vector<float> cubeVertices = {
        1.0f,2.0f,3.0f,  0.5f,-0.5f,-0.5f,  0.5f,0.5f,-0.5f,  -0.5f,0.5f,-0.5f,
        -0.5f,-0.5f,0.5f,   0.5f,-0.5f,0.5f,   -10.0f,-20.0f,-30.0f,   -0.5f,0.5f,0.5f
    };

    std::vector<uint32_t> cubeIndices = {
        4,5,6, 4,6,7,
        0,1,2, 0,2,3,
        0,3,7, 0,7,4,
        1,5,6, 1,6,2,
        3,2,6, 3,6,7,
        0,1,5, 0,5,4
    };
   //
    Engine::Entity cube1;
    cube1.meshID=Engine::LoadMeshTest(cubeVertices);
    Geometry::AABB ab = cube1.GetAABB();
    EXPECT_FLOAT_EQ(ab.max.x, 1.0f);
    EXPECT_FLOAT_EQ(ab.max.y, 2.0f);
    EXPECT_FLOAT_EQ(ab.max.z, 3.0f);
    EXPECT_FLOAT_EQ(ab.min.x, -10.0f);
    EXPECT_FLOAT_EQ(ab.min.y, -20.0f);
    EXPECT_FLOAT_EQ(ab.min.z, -30.0f);



}