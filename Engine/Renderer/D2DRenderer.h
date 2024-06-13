#pragma once

#include <d2d1.h>

#include "../Interfaces/IFinalize.h"

class D2DRenderer : public IFinalize
{
public:
    D2DRenderer();
    ~D2DRenderer() override = default;

    virtual void Initialize(HWND windowHandle, unsigned int width, unsigned int height);
    void Finalize() override;

    virtual void BeginDraw();
    virtual void EndDraw();

private:
    ID2D1Factory* _factory;
    ID2D1HwndRenderTarget* _renderTarget;
};
