#pragma once

#include "Scene.h"

class D2DRenderer;

class BitmapScene : public Scene
{
public:
    BitmapScene();
    BitmapScene(const Scene* parent);
    BitmapScene(const BitmapScene& other) = default;
    BitmapScene(BitmapScene&& other) noexcept = default;
    BitmapScene& operator=(const BitmapScene& other) = default;
    BitmapScene& operator=(BitmapScene&& other) noexcept = default;
    ~BitmapScene() override;

    void Update(float deltaTime) override;
    void Render(const D2DRenderer* renderer) const override;

    void LoadBitmapFromFilename(const std::wstring& path);

    void SetCenter(const Vector& center);
    Vector GetCenter() const;

    Vector GetBitmapSize() const;

protected:
    void UpdateTransform() override;

    Vector _center;
    Matrix _centerMatrix;

    std::wstring _bitmapPath;
    ID2D1Bitmap* _bitmap;
};
