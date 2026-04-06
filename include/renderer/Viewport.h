#pragma once

namespace Renderer{
class Viewport{


    private:
    int x,y,width,height;
    Camera::Camera& camera;

    public:
    Viewport(int x,int y, int width,int height,Camera::Camera& camera):x(x),y(y),width(width),height(height),camera(camera){}

    void setCamera(Camera::Camera& camera){
        this->camera = camera;
    }
    void setOrigin(int x, int y){
        this->x = x;
        this->y = y;
    }
    
    void setSize(int width, height){
        this->width = width;
        this->height = height;
    }
     Camera::Camera& getCamera() { return camera; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }


};
}