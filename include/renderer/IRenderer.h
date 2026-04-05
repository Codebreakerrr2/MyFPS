#pragma once
#include "window/IWindow.h"


namespace MESH {
    class IMeshGpu;
    class IMesh;
}

namespace Asset::Types {
    struct TransformComponent;
    struct MaterialComponent;
}

namespace SHADER {
    class IShader;
}

namespace Camera{
    class Camera;
}
namespace Engine{
    class Registery;
}

namespace Renderer {

 struct drawCommand{
        SHADER::IShader* shader;
        const Asset::Types::MaterialComponent* mat;
         MESH::IMeshGpu* mesh; // const nervig
        const Asset::Types::TransformComponent* trans;
    };


    class IRenderer {
    public:
        virtual ~IRenderer() = default;
        virtual bool init(Window::IWindow* window) = 0;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;
        virtual void clear(float r, float g, float b, float a) = 0;
        virtual void drawTriangle(const Engine::Registery& rg,const Camera::Camera& camera) = 0;
        virtual void filterRenderables(const Engine::Registery& rg) = 0;

    };
}
