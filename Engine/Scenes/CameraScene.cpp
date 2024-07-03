#include "pch.h"
#include "CameraScene.h"
#include "../World/World.h"


void CameraScene::Update(float deltaTime)
{
    UpdateTransform();
    UpdateCullingBound();
    UpdateCenterTransform();
}

void CameraScene::UpdateCullingBound()
{
    _cullingBound.SetCenter(_worldTransform.TransformPoint(_center));
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
}
