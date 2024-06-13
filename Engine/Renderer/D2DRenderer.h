#pragma once

#include <d2d1.h>
#include <wincodec.h>

#include "../Interfaces/IFinalize.h"

class D2DRenderer : public IFinalize
{
public:
    D2DRenderer();
    ~D2DRenderer() override = default;

    virtual void Initialize(HWND windowHandle, unsigned int width, unsigned int height);
    void Finalize() override;

    void BeginDraw() const;
    void EndDraw() const;
    void SetTransform(const D2D1_MATRIX_3X2_F& transform) const;

    
    void DrawBitmap(ID2D1Bitmap* bitmap) const;
    void BitmapFromFile(const wchar_t* path, ID2D1Bitmap** bitmap) const;

private:
    ID2D1Factory* _factory;
    IWICImagingFactory* _imageFactory;
    ID2D1HwndRenderTarget* _renderTarget;
};
