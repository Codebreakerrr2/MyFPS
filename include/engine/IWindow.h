#pragma once

class IWindow {
public:
    virtual ~IWindow() = default;
    virtual bool isOpen() const = 0;
    virtual void close() = 0;
    virtual void getSize(int& width, int& height) const = 0;
    virtual void pollEvents() = 0;
    virtual void swapBuffers() = 0;
    virtual void setBackgroundColor(float r, float g, float b, float a) = 0;
};