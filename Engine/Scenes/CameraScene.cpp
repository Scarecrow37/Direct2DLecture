#include "pch.h"
#include "CameraScene.h"

#include "../Renderer/D2DRenderer.h"
#include "../World/World.h"

CameraScene::CameraScene()
{
    _center = Vector::HalfOne();
}

void CameraScene::Initialize()
{
}

void CameraScene::Update(float deltaTime)
{
    UpdateTransform();
    UpdateCullingBound();
}

void CameraScene::LazyUpdate(float deltaTime)
{
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
    renderer->SetTransform(renderer->GetCameraMatrix());
    renderer->DrawRectangle(_cullingBound.GetRect());
}
