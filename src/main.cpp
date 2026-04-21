
#include <random>
#include <thread>
#include <asset_manager/Factory.h>
#include <asset_manager/Registery.h>
#include "asset_manager/RenderBuffer.h"
#include "profiling/FrameTimer.h"
#include "camera/CameraController.h"
#include "engine/AssetContext.h"
#include "engine/FrameContext.h"
#include "engine/RendererContext.h"
#include "engine/SceneContext.h"
#include "renderer/OpenGLRenderer.h"
#include "renderer/ViewportManager.h"


int main() {

    Context::RendererContext rendererContext(800,600,"FPS",std::make_unique<Renderer::OpenGLRenderer>());
    Context::SceneContext scene_context;
    Context::FrameContext frameContext(&rendererContext, &scene_context);
    Context::AssetContext assetContext;
        MeshID meshId = assetContext.meshManger.create("cube",Factory::cubeMesh);
        ShaderID shaderId=  assetContext.shaderManger.create("shader",Factory::basicShader);




    auto addAssetsAndUpdateBuffer = [&](){
              std::random_device rd;                     // für echten Seed
              std::mt19937 gen(rd());                    // Mersenne Twister Generator

    // 2. Verteilung (float zwischen -50.0 und 50.0)
              std::cauchy_distribution<float> dist(0.0f, 2.0f);



    for (size_t i = 0;i<100000; ++i) {
        EntityID cube = scene_context.rg.createEntity();
        scene_context.rg.add<MeshComponent>(cube,MeshComponent::Init{meshId,&assetContext.meshManger});
        scene_context.rg.add<MaterialComponent>(cube,MaterialComponent::Init{shaderId,&assetContext.shaderManger});
        TransformComponent::Init tc{{dist(gen),dist(gen),dist(gen)},{dist(gen),dist(gen),dist(gen)},{0.3f}};
        scene_context.rg.add<TransformComponent>(cube,tc);
        if (i%50 == 0) {
            LOG_DEBUG(std::to_string(i));
            frameContext.updateReadBuffer();
        }


    }


    };
    std::thread thr{addAssetsAndUpdateBuffer};



rendererContext.viewportManager.creatViewport("fps",0,0,800,600,&scene_context.mainCamera);
rendererContext.rendererSystem.addViewport(
*rendererContext.viewportManager.creatViewport("fps",0,0,800,600,&scene_context.mainCamera)
);

    Profiling::FrameTimer frameTimer;





    while(rendererContext.window.isOpen()) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        frameTimer.beginFrame();
        if (scene_context.keyboard.IsActionPressed(Input::Action::Close)) rendererContext.window.close();

        scene_context.controller.update(scene_context.mainCamera,rendererContext.window.getDeltaTime(),Camera::MoveMode::Flying);

        rendererContext.rendererSystem.getNativeRenderer()->clear(0.5f, 1.0f, 1.0f, 1.0f);

        rendererContext.viewportManager.updateViewports();

        rendererContext.rendererSystem.renderViewports(frameContext.renderBuffer);


        rendererContext.window.swapBuffers();
        rendererContext.window.pollEvents();

        frameTimer.endFrame();
        frameTimer.printFPS();


    }
    thr.join();

    return 0;
}
