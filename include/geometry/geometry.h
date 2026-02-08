#pragma once
#include "Math/Vec.h"


namespace Engine {
    class Camera;
}

struct Ray{
    Math::Vec3 origin;
    Math::Vec3 direction;

    Ray(Math::Vec3 origin, Math::Vec3 direction): origin(origin), direction(Math::Normalize(direction)) {}
};
    void GetMouseRay(Engine::Camera camera);