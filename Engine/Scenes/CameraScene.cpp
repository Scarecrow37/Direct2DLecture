#include "pch.h"
#include "CameraScene.h"

#include "../Renderer/D2DRenderer.h"
#include "../World/World.h"


void CameraScene::Initialize()
{
}

void CameraScene::Update(float deltaTime)
{
    UpdateTransform();
    UpdateCullingBound();
    UpdateCenterTransform();
}

void CameraScene::UpdateCullingBound()
{
    _cullingBound.SetCenter(GetWorldLocation());
}

Matrix CameraScene::GetCameraMatrix() const
{
    return Matrix(_centerMatrix * _worldTransform).Inverse();
}

void CameraScene::UpdateCenterTransform()
{
     _centerMatrix = Matrix::Translation(-_cullingBound.GetExtend());
}

void CameraScene::Render(const D2DRenderer* renderer) const
{
    renderer->SetTransform(_centerMatrix * _worldTransform * renderer->GetCameraMatrix());
    // renderer->DrawRectangle(Rect{_cullingBound.GetMinX(), _cullingBound.GetMinY(), _cullingBound.GetMaxX(), _cullingBound.GetMaxY()});
}
