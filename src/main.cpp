#include <asset_manager/Factory.h>
#include <asset_manager/Registery.h>
#include <engine/EngineContext.h>

#include "camera/CameraController.h"

int main() {

    Engine::EngineContext context;
    context.renderer.init(&context.window);
    EntityID cube = context.rg.createEntity();
    MeshID meshId = context.meshManger.create("cube",Factory::cubeMesh);
   ShaderID shaderId=  context.shaderManger.create("shader",Factory::basicShader);
    context.rg.add<MeshComponent>(cube,MeshComponent::Init{meshId,&context.meshManger});
    context.rg.add<MaterialComponent>(cube,MaterialComponent::Init{shaderId,&context.shaderManger});
    context.rg.add<TransformComponent>(cube);
    Input::InputKeyboard keyboard;
    Input::InputXBOX inputXBOX;
    Input::InputMouse inputMouse;
    Camera::CameraController camera_controller(&keyboard,&inputXBOX,&inputMouse);


    while(context.window.isOpen()) {
        if (keyboard.IsActionPressed(Input::Action::Close)) context.window.close();
        camera_controller.update(context.mainCamera,context.window.getDeltaTime(),Camera::MoveMode::Flying);
        context.renderer.clear(1.0f, 1.0f, 1.0f, 1.0f);
    context.renderer.drawTriangle(context.rg,context.mainCamera);
        context.window.swapBuffers();
        context.window.pollEvents();
    }

    return 0;
}
