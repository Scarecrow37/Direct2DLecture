#pragma once

class Converter;

class RenderTarget
{
    friend class Factory;

public:
    explicit RenderTarget(const std::shared_ptr<ILoggerUnicode>& logger);
    RenderTarget(const RenderTarget& other) = default;
    RenderTarget(RenderTarget&& other) noexcept = default;
    RenderTarget& operator=(const RenderTarget& other) = default;
    RenderTarget& operator=(RenderTarget&& other) noexcept = default;
    ~RenderTarget();

    void BeginDraw() const;
    void EndDraw() const;
    void ClearWhite() const;

    void SetTransform(const D2D1_MATRIX_3X2_F& transform) const;
    void DrawBitmap(ID2D1Bitmap* bitmap) const;

    void CreateBitmapFromWicBitmap(const Converter& converter, ID2D1Bitmap** bitmap) const;

private:
    std::shared_ptr<ILoggerUnicode> _logger;

    ID2D1HwndRenderTarget* _renderTarget;
};
