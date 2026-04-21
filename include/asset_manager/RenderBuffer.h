#pragma once
#include <atomic>
#include <mutex>
#include "Registery.h"
#include "asset_manager/Types.h"
#include "renderer/IRenderer.h"


namespace Context {
    class FrameContext;
}


namespace Engine {
    class EngineContext;
}

namespace Asset::Types {
    class RenderBuffer {
    private:
       std::mutex mtx;
        std::atomic<bool> newSnapshot{false};
       // std::vector<Renderer::drawCommand> registryBuffer; eventuell 3 buffer wenn zu langsam
        std::vector<Renderer::drawCommand> bufferA;
        std::vector<Renderer::drawCommand> bufferB;

        std::vector<Renderer::drawCommand>* writeBuffer = &bufferA;
        std::vector<Renderer::drawCommand>* readBuffer = &bufferB;



        void updateReadBuffer(const Engine::Registery& rg) {
            
                const Asset::Pool<MeshComponent>& meshPool = rg.getPool<MeshComponent>();
                const Asset::Pool<TransformComponent>& transformPool = rg.getPool<TransformComponent>();
                const Asset::Pool<MaterialComponent>& materialPool = rg.getPool<MaterialComponent>();
                std::vector<Renderer::drawCommand> list;

                for(const auto& e : meshPool.getEntities()){
                    if(rg.has<TransformComponent>(e) && rg.has<MaterialComponent>(e)){

                        list.emplace_back(
                            Renderer::drawCommand{
                                materialPool.getComponent(e)->shader(),
                                materialPool.getComponent(e),
                                meshPool.getComponent(e)->meshtupel(),
                                *transformPool.getComponent(e)
                            }
                        );
                    }
                }//--------------------------

                auto compare = [](Renderer::drawCommand& a, Renderer::drawCommand& b){
                    if(a.shader != b.shader) return a.shader<b.shader;
                    if(a.mat->mateirals != b.mat->mateirals) return a.mat->mateirals < b.mat->mateirals;
                    return a.drawCmdMeshTupel < b.drawCmdMeshTupel;
                };
                std::sort(list.begin(),list.end(), compare);
                //-----------------------------
                std::lock_guard<std::mutex> lock(mtx);
                writeBuffer->swap(list);
                newSnapshot.exchange(true,std::memory_order_release);
    
                LOG_INFO("renderables has been updated!");

            }
        

        friend class Context::FrameContext;
        friend class Engine::Registery;

    public:

[[nodiscard]] const std::vector<Renderer::drawCommand>* getBuffer()  {

 if (newSnapshot.load(std::memory_order_acquire)) {
    std::lock_guard<std::mutex> lock(mtx);
    std::swap(readBuffer, writeBuffer);
     LOG_DEBUG("SWAPED BUFFER");
    newSnapshot.store(false, std::memory_order_release);
}
      return readBuffer;
}

    };
}
