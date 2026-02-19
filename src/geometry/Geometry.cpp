#include "geometry/Geometry.h"

#include <cfloat>
#include "engine/Camera.h"
#include "engine/Input.h"
#include "engine/Renderer.h"

namespace Geometry {

    // Necessery TEST FUNCTIONS OF THE FUNCTIONS LOL
//------------------------------------------------------------------------------
    Ray GetMouseRay(Engine::Camera* camera,Math::Vec2 mouseXY)
    {

        double mouseX, mouseY;
        int windowWidth, windowHeight;
        mouseX= mouseXY.x;
        mouseY= mouseXY.y;

        Engine::GetWindowSize(windowWidth, windowHeight);


        double x_ndc = (2.0 * mouseX) / 600 - 1.0;
        double y_ndc = 1.0 - (2.0 * mouseY) / 800;

        Math::Vec4 clip_space(x_ndc, y_ndc, -1.0, 1.0);

        Math::Vec4 camera_space = camera->GetProjectionInverseMatrix() * clip_space;
        // Homogenisierung: w darf nicht 0 sein
        if (camera_space.w != 0.0) {
            camera_space =  camera_space*(1/camera_space.w);
        }

        camera_space.z = -1.0; // bleibt Richtungsvektor
        camera_space.w = 0.0;  // OK jetzt




        Math::Vec4 world_space = camera->GetViewInverseMatrix() * camera_space;

        Math::Vec3 rayDir = Math::Normalize(
            Math::Vec3(world_space.x, world_space.y, world_space.z)
        );

        return Ray(camera->position, rayDir);
    }


















    //________________________________________________________




    Ray GetMouseRay(Engine::Camera* camera)
    {
        double mouseX, mouseY;
        int windowWidth, windowHeight;
        GLFWwindow* window = Engine::GetWindow();

        Engine::GetWindowSize(windowWidth, windowHeight);
        Engine::getMousePosition(window, mouseX, mouseY);

        double x_ndc = (2.0 * mouseX) / windowWidth - 1.0;
        double y_ndc = 1.0 - (2.0 * mouseY) / windowHeight;

        Math::Vec4 clip_space(x_ndc, y_ndc, -1.0, 1.0);

        Math::Vec4 camera_space = camera->GetProjectionInverseMatrix() * clip_space;
        // Homogenisierung: w darf nicht 0 sein
        if (camera_space.w != 0.0) {
            camera_space =  camera_space*(1/camera_space.w);
        }


        camera_space.w = 0.0;

        Math::Vec4 world_space = camera->GetViewInverseMatrix() * camera_space;

        Math::Vec3 rayDir = Math::Normalize(
            Math::Vec3(world_space.x, world_space.y, world_space.z)
        );

        return Ray(camera->position, rayDir);
    }



    bool intersectRayAABB(AABB& box, Ray& ray, float& tHit) {
        // Ray = origin+t*Vektor, so there is a t that gives a point in Ray that is also a point in AABB Box
        // for simplification we take each Axis one by one, lets say we have x min and x max so t should be inside this
        //interval the same goes for y,z if all has the same t and t is inside their max and min then we have intersection

        float tMin = 0.0f;              // Ray startet bei t >= 0
        float tMax = FLT_MAX;

        // --- X ---
        if (ray.direction.x != 0.0f) {
            float tx1 = (box.min.x - ray.origin.x) / ray.direction.x;
            float tx2 = (box.max.x - ray.origin.x) / ray.direction.x;

            float tNear = std::min(tx1, tx2);
            float tFar  = std::max(tx1, tx2);

            tMin = std::max(tMin, tNear);
            tMax = std::min(tMax, tFar);

            if (tMin > tMax) return false;
        } else {
            // Ray parallel zur X-Ebene
            if (ray.origin.x < box.min.x || ray.origin.x > box.max.x)
                return false;
        }

        // --- Y ---
        if (ray.direction.y != 0.0f) {
            float ty1 = (box.min.y - ray.origin.y) / ray.direction.y;
            float ty2 = (box.max.y - ray.origin.y) / ray.direction.y;

            float tNear = std::min(ty1, ty2);
            float tFar  = std::max(ty1, ty2);

            tMin = std::max(tMin, tNear);
            tMax = std::min(tMax, tFar);

            if (tMin > tMax) return false;
        } else {
            if (ray.origin.y < box.min.y || ray.origin.y > box.max.y)
                return false;
        }

        // --- Z ---
        if (ray.direction.z != 0.0f) {
            float tz1 = (box.min.z - ray.origin.z) / ray.direction.z;
            float tz2 = (box.max.z - ray.origin.z) / ray.direction.z;

            float tNear = std::min(tz1, tz2);
            float tFar  = std::max(tz1, tz2);

            tMin = std::max(tMin, tNear);
            tMax = std::min(tMax, tFar);

            if (tMin > tMax) return false;
        } else {
            if (ray.origin.z < box.min.z || ray.origin.z > box.max.z)
                return false;
        }

        // Treffer!
        tHit = tMin;
        return true;
    }
    /*
    bool intersectRayRay(Ray ray, Ray ray2) {
        // if there a t1 and t2 for which ray1 = ray2 then we have intersection
        // this function is not needed acutally, two rays in 3d really hard to intersect lol what for needed?

    }
    */

    bool intersect2AABB(AABB& box, AABB& box2) {
        return std::min(box.max.x,box2.max.x) >= std::max(box.min.x,box2.min.x) &&
            std::min(box.max.y,box2.max.y) >= std::max(box.min.y,box2.min.y) &&
                std::min(box.max.z,box2.max.z) >= std::max(box.min.z,box2.min.z);

    }
}