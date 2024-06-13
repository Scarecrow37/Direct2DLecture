#pragma once

#include <d2d1.h>

class D2DRenderer
{
public:
    D2DRenderer();
    virtual ~D2DRenderer() = default;
    virtual void Initialize(HWND windowHandle, unsigned int width, unsigned int height);
    virtual void Finalize();

private:
    ID2D1Factory* _factory;
    ID2D1HwndRenderTarget* _renderTarget;
};
