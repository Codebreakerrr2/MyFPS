#pragma once
#include "asset_manager/Registery.h"
#include "asset_manager/RenderBuffer.h"
#include "camera/Camera.h"


namespace Context {
    class SceneContext {


    public:
        SceneContext(): controller(&keyboard,nullptr,&mouse) {}
        Engine::Registery& getRegistry() { return rg; }
        Camera::Camera mainCamera;
        Input::InputKeyboard keyboard;
        Input::InputMouse mouse;
        Engine::Registery rg;
        Camera::CameraController controller;
    };
}