#pragma once
#include "Factory.h"
#include "ImagingFactory.h"

class D2DRenderer
{
public:
    explicit D2DRenderer();
    D2DRenderer(const D2DRenderer& other) = default;
    D2DRenderer(D2DRenderer&& other) noexcept = default;
    D2DRenderer& operator=(const D2DRenderer& other) = default;
    D2DRenderer& operator=(D2DRenderer&& other) noexcept = default;
    virtual ~D2DRenderer();

    virtual void Initialize(HWND windowHandle, unsigned int width, unsigned int height);

    void BeginDraw() const;
    void EndDraw() const;
    void SetTransform(const D2D1_MATRIX_3X2_F& transform) const;

    void DrawBitmap(ID2D1Bitmap* bitmap) const;
    void BitmapFromFile(const wchar_t* path, ID2D1Bitmap** bitmap) const;

protected:
    virtual void InitializeCom();

private:
    Factory* _factory;
    ImagingFactory* _imagingFactory;
    RenderTarget* _renderTarget;
};
