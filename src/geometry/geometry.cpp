#include "geometry/geometry.h"

#include "engine/Input.h"
#include "engine/Renderer.h"

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
    camera_space.z = -1.0;
    camera_space.w = 0.0;

    Math::Vec4 world_space = camera->GetViewInverseMatrix() * camera_space;

    Math::Vec3 rayDir = Math::Normalize(
        Math::Vec3(world_space.x, world_space.y, world_space.z)
    );

    return Ray(camera->position, rayDir);
}
