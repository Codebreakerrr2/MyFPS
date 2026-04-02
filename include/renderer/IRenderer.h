#pragma once
#include "window/IWindow.h"


namespace Camera{
    class Camera;
}
namespace Engine{
    class Registery;
}

namespace Renderer {

 struct drawCommand{
        SHADER::IShader* shader;
        Asset::Types::MaterialComponent* mat;
        MESH::IMesh* mesh;
        Asset::Types::TransformComponent* trans;
    };


    class IRenderer {
    public:
        virtual ~IRenderer() = default;
        virtual bool init(Window::IWindow* window) = 0;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;
        virtual void clear(float r, float g, float b, float a) = 0;
        virtual void drawTriangle(const Engine::Registery& rg,const Camera& camera) = 0;
        virtual void filterRenderables(const Engine::Registery& rg) = 0;

    };
}
