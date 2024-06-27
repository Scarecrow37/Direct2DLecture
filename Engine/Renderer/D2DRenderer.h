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
    const Matrix& GetCameraMatrix() const;

private:
    ID2D1HwndRenderTarget* _renderTarget;

    Matrix _cameraMatrix;
};
