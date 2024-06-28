#pragma once

class D2DRenderer
{
public:
    D2DRenderer();
    D2DRenderer(const D2DRenderer& other) = default;
    D2DRenderer(D2DRenderer&& other) noexcept = default;
    D2DRenderer& operator=(const D2DRenderer& other) = default;
    D2DRenderer& operator=(D2DRenderer&& other) noexcept = default;
    ~D2DRenderer();

    void Initialize();
    void Finalize();

    void BeginDraw() const;
    void EndDraw() const;
    void SetTransform(const D2D1_MATRIX_3X2_F& transform) const;

    void DrawBitmap(ID2D1Bitmap* bitmap) const;
    void DrawBitmap(ID2D1Bitmap* bitmap, const Rect& destinationRect, const Rect& sourceRect) const;

    void DrawTextW(const std::wstring& text, float fontSize, const Rect& destinationRect,
                   D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Black),
                   const std::wstring& fontFamily = L"Cooper",
                   DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL,
                   DWRITE_FONT_STYLE style = DWRITE_FONT_STYLE_NORMAL,
                   DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL) const;

    const Matrix& GetCameraMatrix() const;

    size_t GetUsedVRAM() const;

private:
    ID2D1HwndRenderTarget* _renderTarget;
    IDXGIAdapter3* _dxgiAdapter;
    IDWriteFactory* _dWriteFactory;

    Matrix _cameraMatrix;
};
