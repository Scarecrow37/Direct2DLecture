#pragma once


class D2DRenderer
{
public:
    D2DRenderer(const std::shared_ptr<ILoggerUnicode>& logger);
    D2DRenderer(const D2DRenderer& other) = default;
    D2DRenderer(D2DRenderer&& other) noexcept = default;
    D2DRenderer& operator=(const D2DRenderer& other) = default;
    D2DRenderer& operator=(D2DRenderer&& other) noexcept = default;
    virtual ~D2DRenderer() = default;

    virtual void Initialize(HWND windowHandle, unsigned int width, unsigned int height);
    virtual void Finalize() const;

    void BeginDraw() const;
    void EndDraw() const;
    void SetTransform(const D2D1_MATRIX_3X2_F& transform) const;

    void DrawBitmap(ID2D1Bitmap* bitmap) const;
    void BitmapFromFile(const wchar_t* path, ID2D1Bitmap** bitmap) const;

protected:
    virtual void InitializeCom();
    virtual void CreateFactory();
    virtual void CreateImagingFactory();
    virtual void CreateRenderTarget(HWND windowHandle, unsigned int width, unsigned int height);

    std::shared_ptr<ILoggerUnicode> _logger;

private:
    ID2D1Factory* _factory;
    IWICImagingFactory* _imageFactory;
    ID2D1HwndRenderTarget* _renderTarget;
};
