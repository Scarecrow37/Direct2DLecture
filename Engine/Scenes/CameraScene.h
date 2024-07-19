#pragma once
#include "Scene.h"
#include "../Camera/Camera.h"
#include "../Component/Component.h"

class CameraScene : public Scene, public Component, public Camera
{
public:
    CameraScene();
    void Initialize() override;
    void Update(float deltaTime) override;
    void LazyUpdate(float deltaTime) override;
    void Render(const D2DRenderer* renderer) const override;

    void UpdateCullingBound() override;
    Matrix GetCameraMatrix() const override;

protected:
    void UpdateCenterTransform() override;
};
