#pragma once
#include "RendererContext.h"
#include "asset_manager/RenderBuffer.h"
#include "SceneContext.h"

namespace  Context {
    class FrameContext {



        RendererContext* rendererContext = nullptr;
        SceneContext* sceneContext= nullptr;
    public:
        Asset::Types::RenderBuffer renderBuffer;
        FrameContext( RendererContext* rContext,
        SceneContext* sContext):rendererContext(rContext), sceneContext(sContext) {};

        void updateReadBuffer() {
            renderBuffer.updateReadBuffer(sceneContext->getRegistry());
        }
    };
}