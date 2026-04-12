#pragma once
#include <atomic>

#include "Registery.h"
#include "asset_manager/Types.h"
#include "mesh/IMeshPair.h"
#include "renderer/IRenderer.h"


namespace Engine {
    class EngineContext;
}

namespace Asset::Types {
    class RenderBuffer {
    private:
       std::mutex mux;
        std::atomic<bool> newSnapshot{false};
       // std::vector<Renderer::drawCommand> registryBuffer; eventuell 3 buffer wenn zu langsam
        std::vector<Renderer::drawCommand> bufferA;
        std::vector<Renderer::drawCommand> bufferB;

        std::vector<Renderer::drawCommand>* writeBuffer = &bufferA;
        std::vector<Renderer::drawCommand>* readBuffer = &bufferB;



        void updateWriteBuffer(const Engine::Registery& rg) {
            
                const Asset::Pool<MeshComponent>& meshPool = rg.getPool<MeshComponent>();
                const Asset::Pool<TransformComponent>& transformPool = rg.getPool<TransformComponent>();
                const Asset::Pool<MaterialComponent>& materialPool = rg.getPool<MaterialComponent>();
                std::vector<Renderer::drawCommand> list;
                LOG_INFO("started making list");
                for(const auto& e : meshPool.getEntities()){
                    if(rg.has<TransformComponent>(e) && rg.has<MaterialComponent>(e)){
                        LOG_INFO("i");
                        list.emplace_back(
                            Renderer::drawCommand{
                                materialPool.getComponent(e)->shader(),
                                materialPool.getComponent(e),
                                meshPool.getComponent(e)->meshtupel()->getGpuMesh(),
                                transformPool.getComponent(e)
                            }
                        );
                    }
                }//--------------------------
                LOG_INFO("ended making list");
                auto compare = [](Renderer::drawCommand& a, Renderer::drawCommand& b){
                    if(a.shader != b.shader) return a.shader<b.shader;
                    if(a.mat->mateirals != b.mat->mateirals) return a.mat->mateirals < b.mat->mateirals;
                    return a.mesh < b.mesh;
                };
                std::sort(list.begin(),list.end(), compare);
                //-----------------------------
                std::lock_guard<std::mutex> lock(mtx);
                writeBuffer->swap(list);
                newSnapshot.exchange(true,std::memory_order_release);
    
                LOG_INFO("renderables has been updated!");

            }
        

        friend class Engine::EngineContext;
        friend class Engine::Registery;

    public:

[[nodiscard]] const std::vector<Renderer::drawCommand>* getBuffer()  {

 if (newSnapshot.load(std::memory_order_acquire)) {
    std::lock_guard<std::mutex> lock(mtx);
    std::swap(readBuffer, writeBuffer);
    newSnapshot.store(false, std::memory_order_release);
}
      return readBuffer;
}

    };
}
