#pragma once

#include "Scene.h"
#include "../Component/Component.h"

class D2DRenderer;

class BitmapScene : public Scene, public Component
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

    Vector GetBitmapSize() const;

protected:
    void UpdateCenterTransform() override;


    std::wstring _bitmapPath;
    ID2D1Bitmap* _bitmap;
};
