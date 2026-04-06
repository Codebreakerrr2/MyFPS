
#include <random>
#include <asset_manager/Factory.h>
#include <asset_manager/Registery.h>
#include <engine/EngineContext.h>
#include "profiling/FrameTimer.h"
#include "camera/CameraController.h"
#include "renderer/ViewportManager.h"


int main() {

    Engine::EngineContext context;
    context.renderer.init(&context.window);

    std::random_device rd;                     // für echten Seed
    std::mt19937 gen(rd());                    // Mersenne Twister Generator

    // 2. Verteilung (float zwischen -50.0 und 50.0)
    std::uniform_real_distribution<float> dist(-5.0f, 5.0f);



    for (size_t i = 0;i<100; ++i) {
        EntityID cube = context.rg.createEntity();
        MeshID meshId = context.meshManger.create("cube"+std::to_string(i),Factory::cubeMesh);
        ShaderID shaderId=  context.shaderManger.create("shader"+std::to_string(i),Factory::basicShader);
        context.rg.add<MeshComponent>(cube,MeshComponent::Init{meshId,&context.meshManger});
        context.rg.add<MaterialComponent>(cube,MaterialComponent::Init{shaderId,&context.shaderManger});
        TransformComponent::Init tc{{dist(gen)},{dist(gen)},{1}};
        context.rg.add<TransformComponent>(cube,tc);
    }




    Input::InputKeyboard keyboard;
    Input::InputMouse inputMouse;
    Camera::CameraController camera_controller(&keyboard,nullptr,&inputMouse);
    Renderer::Viewport viewport("test",60,0,800,600,&context.mainCamera);
    Renderer::ViewportManager viewportManager(&context.window);
    context.window.setFramebufferSizeCallback([](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
    context.renderer.addViewport(viewport);
    viewportManager.addViewport(viewport);
    Profiling::FrameTimer frameTimer;
    while(context.window.isOpen()) {
        frameTimer.beginFrame();
        if (keyboard.IsActionPressed(Input::Action::Close)) context.window.close();
        camera_controller.update(context.mainCamera,context.window.getDeltaTime(),Camera::MoveMode::Flying);

        context.renderer.clear(0.5f, 1.0f, 1.0f, 1.0f);
        viewportManager.updateViewports();
    context.renderer.renderViewports(context.rg);
        context.window.swapBuffers();
        context.window.pollEvents();
        frameTimer.endFrame();
        frameTimer.printFPS();

    }

    return 0;
}
