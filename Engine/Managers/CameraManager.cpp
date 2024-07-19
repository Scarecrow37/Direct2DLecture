#include "pch.h"
#include "CameraManager.h"

#include "../Renderer/D2DRenderer.h"

CameraManager::~CameraManager()
{
}

void CameraManager::SetActivatedCamera(const int index)
{
    CameraManager& instance = GetInstance();
    if (instance._cameras.find(index) == instance._cameras.end()) return;
    instance._activatedCamera = instance._cameras[index];
    SetWorldCullingBound();
}

void CameraManager::SetActivatedCamera(Camera* camera)
{
    GetInstance()._activatedCamera = camera;
    SetWorldCullingBound();
}

void CameraManager::Initialize(World* world, D2DRenderer* renderer)
{
    CameraManager& instance = GetInstance();
    instance._world = world;
    instance._renderer = renderer;
    SetWorldCullingBound();
    UpdateCameraTransform();
}

void CameraManager::Update()
{
    UpdateCameraTransform();
}

void CameraManager::Finalize()
{
    auto& cameras = GetInstance()._cameras;
    for (auto& camera : cameras)
    {
        delete camera.second;
        camera.second = nullptr;
    }
    cameras.clear();
}

CameraManager& CameraManager::GetInstance()
{
    static CameraManager instance;
    return instance;
}

void CameraManager::SetWorldCullingBound()
{
    const CameraManager& instance = GetInstance();
    if (!instance._activatedCamera || !instance._world) return;
    instance._world->SetCullingBound(instance._activatedCamera->GetCullingBound());
}

void CameraManager::UpdateCameraTransform()
{
    const CameraManager& instance = GetInstance();
    if (!instance._activatedCamera || !instance._renderer) return;
    instance._renderer->SetCameraMatrix(instance._activatedCamera->GetCameraMatrix());
}
