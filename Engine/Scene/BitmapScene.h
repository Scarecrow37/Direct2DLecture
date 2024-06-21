#pragma once

#include "Scene.h"

class D2DRenderer;

class BitmapScene : public Scene
{
public:
    BitmapScene(const std::shared_ptr<ILoggerUnicode>& logger);
    BitmapScene(const std::shared_ptr<ILoggerUnicode>& logger, const Scene* parent);
    BitmapScene(const BitmapScene& other) = default;
    BitmapScene(BitmapScene&& other) noexcept = default;
    BitmapScene& operator=(const BitmapScene& other) = default;
    BitmapScene& operator=(BitmapScene&& other) noexcept = default;
    ~BitmapScene() override;

    void Update(float deltaTime);
    void Render(const D2DRenderer& renderer) const;

    void Load(const D2DRenderer& renderer, const std::wstring& path);

    void SetCenter(const Vector& center);
    Vector GetCenter() const;

protected:
    void UpdateTransform() override;

    Vector _center;
    Matrix _centerMatrix;

    std::wstring _path;
    ID2D1Bitmap* _bitmap;
};
